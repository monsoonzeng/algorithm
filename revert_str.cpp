#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    const int max_word_size = 50;
    char buffer[100];
    char *buffer_start = buffer;
    char *buffer_end = buffer; // point not used buffer
    bool buffer_save_right = false;
    bool pre_is_word = false;
    char *empty_pos;
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
                memcpy(buffer+max_word_size, end_blank+1, end_length);
                // swap left and buffer
                memcpy(end-start_length+1, start, start_length);
                memcpy(start, buffer+max_word_size, start_length);
                // update buffer_save_right and buffer_start buffer_end
                buffer_start = buffer + max_word_size + start_length;
                buffer_end = buffer + max_word_size + end_length;
                buffer_save_right = true;
                empty_pos = end_blank+1;
            } else if(start_length == end_length) {
                // swap right and left
                memcpy(buffer, end_blank+1, end_length);
                memcpy(end_blank+1, start, end_length);
                memcpy(start, buffer, end_length);
                empty_pos = NULL;
            } else {
                // copy left to buffer
                memcpy(buffer, start, start_length);
                // swap left and buffer
                memcpy(start, end_blank+1, end_length);
                memcpy(end_blank+1, buffer+(start_length-end_length), end_length);
                // update buffer_save_right and buffer_start buffer_end
                buffer_start = buffer;
                buffer_end = buffer + start_length-end_length;
                buffer_save_right = false;
                empty_pos = start+end_length;
            }
            // update start and end;
            start = start_blank;
            end = end_blank;
        } else if (buffer_save_right) {
            if (start > end) {
                // copy buffer to start
                // memcpy(start, buffer_start, buffer_end-buffer_start);
                //memcpy(start-buffer_end+buffer_start, buffer_start, buffer_end-buffer_start);
                memcpy(empty_pos, buffer_start, buffer_end-buffer_start);
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
            if (start_length <= end_length) {
                // swap left and buffer
                memcpy(end+1+end_length-start_length, start, start_length);
                memcpy(start, buffer_start, start_length);
                // update buffer_start buffer_end
                buffer_start += start_length;
                empty_pos = end+1;
            } else {
                // swap start and buffer, buffer change
                memcpy(end+1, start+start_length-end_length, end_length);
                memcpy(buffer, start, start_length-end_length);
                memcpy(start, buffer_start, end_length);
                // update buffer_start buffer_end buffer_save_right
                buffer_start = buffer;
                buffer_end = buffer+start_length-end_length;
                buffer_save_right = false;
                empty_pos = start+end_length;
            }
            // update start
            start = start_blank;
        } else  {
            // buffer save left
            if (start > end) {
                // copy buffer to end
                // memcpy(end-(buffer_end-buffer_start), buffer_start, buffer_end-buffer_start);
                memcpy(empty_pos, buffer_start, buffer_end-buffer_start);
                // memcpy(start, buffer_start, buffer_end-buffer_start);
                break;
            }
            // swap buffer and end
            if (pre_is_word) {
                for (end_blank = end; *end_blank == ' ' && end_blank >= start; --end_blank) {}
            } else {
                for (end_blank = end; *end_blank != ' ' && end_blank >= start; --end_blank) {}
            }
            start_length = buffer_end - buffer_start;
            end_length = end - end_blank;
            if (start_length <= end_length) {
                // swap buffer and end, buffer change
                memcpy(start-start_length, end_blank+1, start_length);
                memcpy(buffer+max_word_size, end_blank+1+start_length, end_length - start_length);
                memcpy(end_blank+1, buffer_start, start_length); 
                //buffer change
                buffer_start = buffer+max_word_size;
                buffer_end = buffer_start + end_length-start_length;
                buffer_save_right = true;
                empty_pos = end_blank+1;
            } else {
                // swap buffer and end
                memcpy(start-start_length, end_blank+1, end_length);
                memcpy(end_blank+1, buffer_end-end_length, end_length);
                // update buffer_end
                buffer_end -= end_length;
                empty_pos = start-start_length+end_length;
            }
            end = end_blank;
        }
        // next is find consecutive blank or word start 
        pre_is_word = !pre_is_word;
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
    /*
     strcpy(src, "i am going to school");
    printf("%s\n", src);
    length = strlen(src);
    revert_new(src, length);
    printf("%s\n", src);
     strcpy(src, "i am");
    printf("%s\n", src);
    length = strlen(src);
    revert_new(src, length);
    printf("%s\n", src);
     strcpy(src, "am i");
    printf("%s\n", src);
    length = strlen(src);
    revert_new(src, length);
    printf("%s\n", src);
     strcpy(src, "are i");
    printf("%s\n", src);
    length = strlen(src);
    revert_new(src, length);
    printf("%s\n", src);
     strcpy(src, "i are");
    printf("%s\n", src);
    length = strlen(src);
    revert_new(src, length);
    printf("%s\n", src);
*/
    get_str(src, length);
    length = strlen(src);
    printf("%s\n", src);
    CLOCK_START;
//    revert(src, length);
    revert_new(src, length);
    printf("%s\n", src);
    PRINT_TIME_USED;
    
    return 0;
}
