#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t g_clock_start;
#define CLOCK_START (g_clock_start=clock());
#define PRINT_TIME_USED printf("%s:%s(%d) Run time:%d\n",__FILE__, __FUNCTION__, __LINE__, \
            (clock()-g_clock_start));

void revert_new(char *src, int length) 
{
    char *start;
    char *end;
    char *start_blank;
    char *end_blank;
    int start_length;
    int end_length;
    char buffer[50];
    char *buffer_start = buffer;
    char *buffer_end = buffer; // point not used buffer
    bool buffer_save_right = false;
    bool pre_is_word = false;
    for (start=src, end=src+length-1; start < end || buffer_start != buffer_end; ) {
        if (buffer_start == buffer_end) {
            // buffer empty, swap start and end
            if (pre_is_word) {
                // find next not ' '
                for (start_blank = start; *start_blank == ' ' && start_blank <= end; ++start_blank) {}
                for (end_blank = end; *end_blank == ' ' && end_blank >= start; --end_blank) {}
            } else {
                // find next ' ' 
                for (start_blank = start; *start_blank != ' ' && start_blank <= end; ++start_blank) {}
                for (end_blank = end; *end_blank != ' ' && end_blank >= start; --end_blank) {}
            }
            if (start_blank > end) {
                break;
            }
            start_length = start_blank - start;
            end_length = end - end_blank;
            if (start_length < end_length) {
                // copy right to buffer
                memcpy(buffer, end_blank+1, end_length);
                // swap left and buffer
                memcpy(end-start_length+1, start, start_length);
                memcpy(start, buffer, start_length);
                // update buffer_save_right and buffer_start buffer_end
                buffer_start = buffer + max_word_size + start_length;
                buffer_end = buffer + max_word_size + end_length;
                buffer_save_right = true;
            } else if(start_length == end_length) {
                // swap right and left
                memcpy(buffer, end_blank+1, end_length);
                memcpy(end_blank+1, start, end_length);
                memcpy(start, buffer, end_length);
            } else {
                // copy left to buffer
                memcpy(buffer, start, start_length);
                // swap left and buffer
                memcpy(start, end_blank+1, end_length);
                memcpy(end_blank+1, start+(start_length-end_length), end_length);
                // update buffer_save_right and buffer_start buffer_end
                buffer_start = buffer;
                buffer_end = buffer + start_length-end_length;
                buffer_save_right = false;
            }
            // update start and end;
            start = start_blank;
            end = end_blank;
        } else if (buffer_save_right) {
            if (start > end) {
                // copy buffer to start
                memcpy(start, buffer_start, buffer_end-buffer_start);
                break;
            }
            // swap start and buffer
            if (pre_is_word) {
                for (start_blank = start; *start_blank == ' ' && start_blank <= end; ++start_blank) {}
            } else {
                for (start_blank = start; *start_blank != ' ' && start_blank <= end; ++start_blank) {}
            }
            start_length = start_blank - start;
            end_length = buffer_end - buffer_start;
            if (start-length <= end_length) {
                // swap left and buffer
                memcpy(end+1+end_length-start_length, start, start_length);
                memcpy(start, buffer_start, start_length);
                // update buffer_start buffer_end
                buffer_start += start_length;
            } else {
                memcpy(end+1, start+start_length-end_length, end_length);
                memcpy(start, buffer_start, end_length);
                // buffer change
                memcpy(buffer, start, start_length-end_length);
                // update buffer_start buffer_end buffer_save_right
                buffer_start = buffer;
                buffer_end = buffer+start_length-end_length;
                buffer_save_right = false;
            }
            // update start
            start = start_blank;
        } else  {
            if (start > end) {
                // copy buffer to end
                memcpy(end-(buffer_end-buffer_start), buffer, buffer_end-buffer_start);
                break;
            }
            // swap buffer and end
            if (pre_is_word) {
                for (end_blank = end; *end_blank == ' ' && end_blank >= start; --end_blank) {}
            } else {
                for (end_blank = end; *end_blank == ' ' && end_blank >= start; --end_blank) {}
            }
            start_length = buffer_end - buffer_start;
            end_length = end - end_blank;
        }
        // next is find consecutive blank or word start 
        pre_is_word = !pre_is_word;
        // useless
        for (start_blank = start; *start_blank !=' ' && *start_blank !='\0'; ++start_blank) {}
        for (end_blank = end; *end_blank != ' ' && end_blank >= src; --end_blank) {}
        start_length = start_blank - start;
        end_length = end - end_blank;
        if (start_length == end_length) {
            // swap [start,start_blank) (end_blank,end]
            // update start and end
        } else if (start_length < end_length) {
            //swap [start, start_blank) [end_blank, end-(end_length-start_length))
            //save [end-(end_length-start_length), end] to buffer

        } else if (start_length > end_length) {
            // swap and save start to buffer
        }
        // update start and end

    }
}
void revert(char*src, int length) {
    char tmp;
    char *start_blank;
    char *tmp_index;
    char *end;
    char *start;
    for (start=src, end=src+length-1; start<end; ++start, --end) {
         tmp = *start;
         *start = *end;
         *end = tmp;
    }
    for (tmp_index=src; tmp_index < src+length; ) {
        for (start_blank=tmp_index; *start_blank != ' ' && *start_blank != '\0'; ++start_blank) {}
        for (start=tmp_index, end=start_blank-1 ; start < end; ++start, --end) {
            tmp = *start;
            *start = *end;
            *end = tmp;
        }
        //add tmp_index
        tmp_index = start_blank+1;
    }
}

void get_str(char *src, int length) 
{
    for (int i=0; i<length; ++i) {
        if (i % 30 == 29) {
            src[i] = ' ';
        } else {
            int off = rand()%27;
            if (off == 26) {
                src[i] = ' ';
            } else {
                src[i] = 'a'+off;
            }
        }
    }
    src[length-1] = '\0';
}
int main()
{
    int length = 128;
    char *src = new char[length];
    get_str(src, length);
    printf("%s\n", src);
    CLOCK_START;
    revert(src, length-1);
    printf("%s\n", src);
    PRINT_TIME_USED;
    
    return 0;
}
