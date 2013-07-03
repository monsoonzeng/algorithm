#include <stdio.h>


void revert(char *src, int length) 
{
    for (start=src, end=src+length-1; start < end; ) {
        for (start_blank = start; start_blank !=' ' && start_blank !='\0'; ++start_blank) {}
        for (end_blank = end; end_blank != ' ' && end_blank >= src; --end_blank) {}
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
int main()
{
    return 0;
}
