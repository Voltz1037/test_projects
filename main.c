#include<ncurses.h>
#include <locale.h>
#include <string.h>
#include <sys/types.h>   
#include <dirent.h>
#include <time.h>
//#include <readdir.h>

void printpath(WINDOW* window);
void printtime(WINDOW* window);
void uscanf(void);
void refresh_time(void);
int main()
{
        int key;
         int x = 0, y = 0; // 初始化光标位置
        //初始化ncurses
        setlocale(LC_ALL,"");
        initscr();
        cbreak();            // 禁用行缓冲  
        noecho();            // 禁用回显  
        keypad(stdscr,1); // 启用功能键（如方向键）
        start_color(); // 启用颜色功能
        init_pair(1, COLOR_GREEN, COLOR_WHITE);
        init_pair(2, COLOR_BLACK, COLOR_WHITE);
        // 创建一个新窗口
    WINDOW* window = newwin(50, 70, 0, 0);
     box(window, 0, 0); // 绘制窗口边框
      // 在窗口中显示文本
    mvwprintw(window, 1, 1, "对话区：");
    mvwprintw(window, 10, 1, "--------------------------------------------------------------------");
    
        //循环等待用户输入
        while(key != 'q') {
        
                key = getch();
                switch (key){
                        case KEY_UP:
                                wmove(window, y--, x);
                                break;
                        case KEY_DOWN:
                                wmove(window, y++, x);
                                break;
                        case KEY_LEFT:
                                wmove(window, y, x--);
                                break;
                        case KEY_RIGHT:
                                wmove(window, y, x++);
                                break;
                        default:
                                waddch(window, key);
                                break;
                }
                //刷新屏幕以显示新输出
                printtime(window);
                wmove(window, y, x);
                refresh();
                wrefresh(window);
        }
 
        //结束ncurses模式
        endwin();
        return 0;
}

void printtime(WINDOW* window)
{
    // 获取当前时间
    time_t now = time(NULL);
    struct tm *local_time = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    // 在窗口中显示时间
    mvwprintw(window, 2, 1, "当前时间：%s", time_str);
}
/*void printpath(WINDOW* window)
{
    // 获取目录中所有的文件路径
    const char *dir_path = "111";
    pathInfo *path_info = init_head_node();
    read_dir_ex(dir_path, path_info);
    //printf("==========================\n");
    pathInfo *info = path_info->next;
    //printf("head: %p, %p\n", path_info->pre, path_info->next);
    mvwprintw(window, 3, 1, "head: %p, %p\n", path_info->pre, path_info->next);
    while(info) {
        mvwprintw(window, 4, 1, "%p, %p, %p, %d, %s\n", info, info->pre, info->next, info->isdir, info->name);
        info = info->next;
    }
    free_memory(path_info); // 释放内存空间

}*/
