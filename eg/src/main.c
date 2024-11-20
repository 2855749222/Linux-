#include "app.h"

int main()
{
    //app初始化
    app_run();

    while(1)
    {
        //登录注册模块
        if(login_main() == false)
        {
            break;
        }

        //主界面
        draw_main();
    }

    //退出app
    app_quit();
    
    return 0;
}