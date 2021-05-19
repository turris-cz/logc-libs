/* Copyright (c) 2021 CZ.NIC z.s.p.o. (http://www.nic.cz/)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <czmq_logc.h>
#include <stdio.h>
#include <string.h>

LOG(czmq);


// ZMQ formats log messages with level, date and time prefixed. An example of such
// log line is:
//   E: 21-05-19 21:30:11 test message: foo

static struct cookie {
	char *buf;
	size_t siz;
} cookie;
static FILE *file;


// Unfortunatelly zmq provides access to only already formated string so to get
// level we have to parse it. Thankfully it is just simply first char.
enum log_message_level get_level(const char buf0) {
	switch (buf0) {
		case 'E':
			return LL_ERROR;
		case 'W':
			return LL_WARNING;
		case 'N':
			return LL_NOTICE;
		case 'I':
			return LL_INFO;
		case 'D':
			return LL_DEBUG;
		default: // Anything else is parsing error so we report it as error
			return LL_ERROR;
	}
}

ssize_t zmq_write(void *_, const char *buf, size_t size) {
	size_t len = size;
	while (len > 0) {
		const char *end = memchr(buf, '\n', len);
		if (end == NULL) {
			cookie.buf = realloc(cookie.buf,
					(cookie.siz + len) * sizeof *cookie.buf);
			memcpy(cookie.buf + cookie.siz, buf, len);
			cookie.siz += len;
			cookie.buf[cookie.siz] = '\0';
			break;
		}
		len -= end - buf + 1;
		enum log_message_level level = get_level(buf[0]);
		// Skip three space separated blocks. Those are level, date and time.
		for (int i = 0; i < 3; i ++)
			buf = memchr(buf, ' ', end - buf) + 1;
		// The rest is the message
		logc(log_czmq, level, "ZMQ: %s%.*s", cookie.buf, (int)(end - buf), buf);
		cookie.buf[0] = '\0';
		cookie.siz = 0;
		buf = end + 1;
	}
	return size; // we always consume all data
}


void logc_czmq_init() {
	cookie.buf = strdup("");
	cookie.siz = 0;
	file = fopencookie(NULL, "w", (cookie_io_functions_t){.write = zmq_write});
	zsys_set_logstream(file);
	// zsys_set_logstream tries to query for file backend but that of course fails
	// because file does not have to belong to any file. That causes no issue
	// except that zmq fails to clean errno after itself.
	errno = 0;
}

void logc_czmq_cleanup() {
	zsys_set_logstream(stdout);
	fclose(file);
	free(cookie.buf);
}
