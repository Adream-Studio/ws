# ws(web site || web search)
A command line application to conveniently visit website or search something by using your web browser.


## Installation
Download the ZIP pacakage, unpack it into some *path*, add this *path* to your **Environment Variables List** , make some config files in folder "config",  then you can call it in the CMD or any other Ternimal.

#### **A config file may be like this:**

*File name* : github

*File content* : 
```
https://github.com
https://github.com/search?q=
```
## Usage
```
ws [config name] [<things you want to search>]

example1 : ws github 
example2 : ws github something-can-open-websites-in-terminal
```
## Remain to be done
1. error()
2. add_onfig()
3. remove_config()
4. edit_config()
5. show_config()