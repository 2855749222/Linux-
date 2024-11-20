#include "include/login.h"
int samenum(array *n, char *cun)
{
    int length = 0;
    char *len = cun;
    while (*len != '\0')
    { // 循环直到遇到字符串的结尾'\0'
        length++;
        len++;
    }

    for (int i = 0; i < n->index && i < length; i++)
    {
        if (cun[i] != n->data[i])
        {
            return 0;
        }
    }

    if (n->index != length)
    {
        return 0;
    }
    return 1;
}
int same(array *cur) // 判断账号密码是否正确
{
    Restatus = 0; //给定注册状态
    FILE *userFile = fopen("/mnt/share/aibum/file/user.txt", "r");
    if (userFile == NULL)
    {
        printf("不能打开不存在的文件");
    }
    array *curpwd = passwd;
    if (cur == Reper)
    {
        curpwd = Repwd;
    }
    if (cur->index == 0)
    {
        show_error_login("请输入账号", 290, 150);
        return 0;
    }
    if (curpwd->index == 0)
    {
        show_error_login("请输入密码", 290, 210);
        return 0;
    }
    char percun[30];
    char pwdcun[30];
    int person_status = 0;
    int passwd_status = 0;
    while (fscanf(userFile, "User : %s , passwd : %s *\n", percun, pwdcun) != EOF)
    {
        printf("\n%s\n", percun);
        printf("\n%s\n", pwdcun);
        person_status = samenum(cur, percun);
        passwd_status = samenum(curpwd, pwdcun);
        if (person_status == 1) // 找到账号了
        {
            printf("找到账号了");
            break;
        }
    }
    int result = fclose(userFile);
    if (result != 0)
    {
        printf("关闭文件失败");
        return 1;
    }
    if (cur == Reper) // 为注册账号
    {
        if (person_status == 1)
        {
            show_error_login("账号已注册", 350, 180);
            Reper->index = 0;
            Repwd->index = 0;
            sleep(2);
            show_mmap(Registd);
            showfont(Reper, 290, 150, 200, 25);
            showfont(Repwd, 290, 210, 200, 25);
            Restatus = 2;
           
        }
        else
        {
            Restatus = 1;
        }
    }
    else
    {
        if (!person_status && !passwd_status)
        {
            show_error_login("账号密码错误", 350, 180);
            sleep(2);
            show_mmap(logininput);
            person->index = 0;
            passwd->index = 0;
            showfont(person, 290, 150, 200, 25);
            showfont(passwd, 290, 210, 200, 25);
        }
        else if (!person_status && passwd_status)
        {
            show_error_login("账号错误", 350, 180);
            sleep(2);
            show_mmap(logininput);
            person->index = 0;
            showfont(person, 290, 150, 200, 25);
            showfont(passwd, 290, 210, 200, 25);
        }
        else if (person_status && !passwd_status)
        {
            show_error_login("密码错误", 350, 180);
            sleep(2);
            show_mmap(logininput);
            passwd->index = 0;
            showfont(person, 290, 150, 200, 25);
            showfont(passwd, 290, 210, 200, 25);
        }
        else
        {
            show_error_login("登陆成功", 350, 180);
            status = 0;
        }
    }
    return 1;
}

void loginto(array *cur, int pox, int poy) // 用户密码框
{

    int x, y;
    while (1)
    {

        touch_wait(&x, &y);
        Restatus = 0;
        if (x > 270 && x < 560 && y > 120 && y < 180)
        {
            if (cur == passwd)//判读是登录框还是注册框
                cur = person;
            if (cur == Repwd)//判读是登录框还是注册框
                cur = Reper;
            poy = 150; //设置文字显示位置
        }
        else if (x > 270 && x < 560 && y > 210 && y < 250)
        {
            if (cur == person)//判读是登录框还是注册框
                cur = passwd;
            if (cur == Reper)
                cur = Repwd;
            poy = 210;
        }
        else if (x > 270 && x < 325 && y > 290 && y < 340)
        {
            cur->data[cur->index++] = '7';
            showfont(cur, pox, poy, 200, 25);//显示文字
        }
        else if (x > 332 && x < 385 && y > 290 && y < 340)
        {
            cur->data[cur->index++] = '8';
            showfont(cur, pox, poy, 200, 25);//显示文字
        }
        else if (x > 393 && x < 440 && y > 290 && y < 340)
        {
            cur->data[cur->index++] = '9';
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 270 && x < 325 && y > 350 && y < 400)
        {
            cur->data[cur->index++] = '4';
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 332 && x < 385 && y > 350 && y < 400)
        {
            cur->data[cur->index++] = '5';
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 393 && x < 440 && y > 350 && y < 400)
        {
            cur->data[cur->index++] = '6';
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 270 && x < 325 && y > 405 && y < 455)
        {
            cur->data[cur->index++] = '1';
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 332 && x < 385 && y > 405 && y < 455)
        {
            cur->data[cur->index++] = '2';
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 393 && x < 440 && y > 405 && y < 455)
        {
            cur->data[cur->index++] = '3';
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 450 && x < 575 && y > 250 && y < 270)//立即注册/登录
        {
            if (cur == Reper || cur == Repwd)//判断是登录还是注册
            {
                return;
            }
            Regist();
        }
        else if (x > 460 && x < 534 && y > 290 && y < 340)//退格
        {
            if (cur->index != 0)
            {
                cur->index--;
            }
            printf("cur->index:%d", cur->index);//下标减一
            showfont(cur, pox, poy, 200, 25);
        }
        else if (x > 450 && x < 540 && y > 400 && y < 455)//确认键
        {
            if (cur == Reper || cur == Repwd)//如果是注册
            {
                printf("注册");
                if(same(Reper) == 0 || Restatus != 1)
                {
                    continue;
                }
                break;

                
            }
            //不是注册
            same(person);
            if (status == 0)
            {
                return;
            }
        }
        else if (x > 600 || x < 100)//退出
        {
            return;
        }
    }
}
void Regist() // 注册
{
    char *filename = "/mnt/share/aibum/file/user.txt";
    FILE *ioFile = fopen(filename, "a+"); // 使用 a+ 模式以追加方式打开文件，如果文件不存在则创建
    if (ioFile == NULL)
    {
        printf("打开文件失败\n");
        return;
    }

    Reper = malloc(sizeof(array));
    Repwd = malloc(sizeof(array));
    if (!Reper || !Repwd)
    {
        printf("内存分配失败\n");
        fclose(ioFile);
        free(Reper);
        free(Repwd);
        return;
    }
    Reper->index = 0;
    memset(Reper->data, 0, 30);
    Repwd = malloc(sizeof(array));
    Repwd->index = 0;
    memset(Repwd->data, 0, 30);
    loginto(Reper, 290, 150);
    printf("注册%d\n", Restatus);
    if (Restatus == 1)
    {
        char user[30];
        memset(user, 0, 30);
        char pwd[30];
        memset(pwd, 0, 30);
        for (int i = 0; i < Reper->index; i++)
        {
            user[i] = Reper->data[i];
        }
        for (int i = 0; i < Repwd->index; i++)
        {
            pwd[i] = Repwd->data[i];
        }
        printf("per:%s", user);
        printf("pwd:%s", pwd);
        int fprintfR = fprintf(ioFile, "User : %s , passwd : %s *", user, pwd);
        if (fprintfR == EOF)
        {
            printf("写入字符串失败");
        }
        else
        {
            show_error_login("注册成功", 350, 180);
            sleep(2);
            printf("写入字符串成功:%d\n", fprintfR);
        }
        Restatus = 0;
    }

    fclose(ioFile);
    return ;
}
void main(int argc, char const *argv[])
{
    int **login = load_bmp_as_argb("image/login.bmp");
    logininput = load_bmp_as_argb("image/logininput.bmp");
    Registd = load_bmp_as_argb("image/RegistrationForm.bmp");
    person = malloc(sizeof(array));
    person->index = 0;
    memset(person->data, 0, 30);
    passwd = malloc(sizeof(array));
    passwd->index = 0;
    memset(passwd->data, 0, 30);
    show_mmap(login);

    int x, y;
    while (status)//登录界面循环
    {
        touch_wait(&x, &y);
        if (x > 270 && x < 560 && y > 120 && y < 180)//点击用户文本框
        {
            show_mmap(logininput);
            loginto(person, 290, 150);//调用输入函数 传入数组指针
        }
        else if (x > 270 && x < 560 && y > 210 && y < 250)//点击密码文本框
        {
            show_mmap(logininput);
            loginto(passwd, 290, 210);
        }
        else if (x > 450 && x < 575 && y > 250 && y < 270)//注册按钮
        {
            show_mmap(Registd);//注册页面渲染
            Regist();//注册函数
            show_mmap(logininput);//成功返回登录页面
        }
        else
        {
            show_mmap(login);//点击其他地方返回登录页面
            showfont(person, 290, 150, 200, 25);//显示用户名
            showfont(passwd, 290, 210, 200, 25);//显示密码
        }
    }
}
