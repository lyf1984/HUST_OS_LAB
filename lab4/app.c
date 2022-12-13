#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

int main(char argc, char * argv[])
{
    int fd;
    int ret;
    int buf[2] = {128,64};
    int max_num = 0;
    printf("请输入第一个数:");   
    scanf("%d",&buf[0]);
    printf("请输入第二个数:"); 
    scanf("%d",&buf[1]);
     //将要打开的文件的路径通过main函数的参数传入
    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    
    fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        perror("fail to open file\n");
        return -1;
    }
    //write data 
    ret = write(fd, buf, sizeof(buf));
    if (ret < 0)
    {
        printf("write  err!\n");
        return -1;
    }
    printf("before read:buf:[%d,%d] max_num:%d\n",buf[0],buf[1],max_num);
    ret = read(fd,&max_num,sizeof(max_num));
   if(ret<0)  
    {
        printf("read  err!\n");
        return -1;
    }
    printf("after read:buf:[%d,%d] max_num:%d\n",buf[0],buf[1],max_num);
    close(fd);
    return 0;
}
