#include "menuClass.h"

MenuClass::MenuClass()
{

}

MenuClass::~MenuClass()
{

}



QString startMenu(MainWindow * monitori)
{
    QString text="<span style = \" align = center; vertical-align = middle\"><br><br>Welcome to <br>Bank</span>";
    QStringList text_list; // I use this to store lines of text
    //   text_list << "> Jokin muu summa";
    //   text_list << "> 20 euroa";
    //   text_list << "< 40 euroa";
    //   text_list << "> 50 euroa";
    //   text_list << "> 100 euroa";
    text_list << "> Posion pankki ";
    text_list << "<Welcome to";
    text_list << "<Bank";

    QString html_style("<style>"
                       "p.add{font-size: 25px; color: black; text-align:right;  margin: 10px; padding: 0; margin-right: 20px; padding-right : 10px;}"
                       "p.remove{font-size: 40px; color: black; text-align:center;margin: 10px;}"
                       "</style>");

    QString format_add = "<p class=\"add\">%1</p>"; // we use these to make formatting easier
    QString format_remove = "<p class=\"remove\">%1</p>"; // basically helps us add tags before and after our text

//    QString text; // this is a variable we will use to append our text as HTML code

    for(int i = 0; i < text_list.length(); i++)
    {
        if(text_list[i].startsWith(">")) // detect if the line was added
            text.append(format_add.arg(text_list[i].replace(">", " "))); // add the line in our html code, but replace > character with a character entity

        else if(text_list[i].startsWith("<")) // detect if the line was removed
            text.append(format_remove.arg(text_list[i].replace("<", ""))); // add the line in our html code, but replace < character with a character entity

    }
    //
    monitori -> monitorOutput("testiteksti");
    return text;
}
//        QString a;
//        a.append("testiteksti");
//        a.MainWindow::monitorOutput();




