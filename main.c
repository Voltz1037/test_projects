//g++ main.c -o main -lncursesw
#include<ncurses.h>
#include <locale.h>
#include <string.h>
#include <sys/types.h>   
#include <dirent.h>
#include <time.h>
#include <pthread.h>
#include<unistd.h>
//#include <readdir.h>

int key;
int x = 9, y = 13; // 初始化光标位置
WINDOW* window;
void printpath(WINDOW* window);
void printtime(WINDOW* window);
void* uscanf(void*){
 //循环等待用户输入
        while(key != 'q') {
        
                key = getch();
                switch (key){
                        case KEY_UP:
                                wmove(window, y--, x);
                                if(y==12){
                                    y++;
                                }
                                break;
                        case KEY_DOWN:
                                wmove(window, y++, x);
                                break;
                        case KEY_LEFT:
                                wmove(window, y, x--);
                                if(x==1){
                                    x=67;y--;
                                }
                                break;
                        case KEY_RIGHT:
                                wmove(window, y, x++);
                                if(x==69){
                                    x=1;y++;
                                }
                                break;
                        default:
                                if(0<key&&key<255){
                                waddch(window, key);
                                x++;
                                if(x==68){
                                    x=1;y++;
                                }
                                break;}
                                else break;
                }
                refresh();
                wrefresh(window);
        }
        endwin();
}
void* refresh_time(void*){
while (1){
delay_output(1000);
printtime(window);
wmove(window, y, x);
wrefresh(window);
}

}
int main()
{
        
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
    window = newwin(50, 70, 0, 0);
     box(window, 0, 0); // 绘制窗口边框
      // 在窗口中显示文本
    mvwprintw(window, 1, 1, "对话区：");
    mvwprintw(window, 10, 1, "--------------------------------------------------------------------");
    printpath(window);
    mvwprintw(window, 12, 1, "--------------------------------------------------------------------");
    mvwprintw(window, 13, 1, "输入区：");

    pthread_t t1,t2;
    pthread_create(&t1,NULL,refresh_time,NULL);
    pthread_create(&t2,NULL,uscanf,NULL);
    pthread_join(t2,NULL);
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
    char* timedisplay;
    timedisplay=&time_str[11];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", local_time);
    // 在窗口中显示时间
    attron(COLOR_PAIR(2));
    mvwprintw(window, 11, 61, "%s",timedisplay);
    attroff(COLOR_PAIR(2)); 
    wmove(window, y, x);
}

void printpath(WINDOW* window){
char path[105];
getcwd(path,sizeof(path));
if((path[0]=='/')&&(path[1]=='h')&&(path[2]=='o')&&(path[3]=='m')&&(path[4]=='e')){
    for(int i=0;i<101;i++){
        path[i]=path[i+4];
    }
     path[0]='~';
}
attron(COLOR_PAIR(1));
mvwprintw(window, 11, 1, "%s", path);
attroff(COLOR_PAIR(1));  // 关闭文本属性
}