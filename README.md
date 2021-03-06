# ws(web site || web search)
A command line application to conveniently visit website or search something by using your web browser.

![](https://img.shields.io/badge/Windows-Yes-blue.svg)
![](https://img.shields.io/badge/Linux-Yes-blue.svg)
![](https://img.shields.io/badge/MacOS-No-red.svg)
![](https://img.shields.io/badge/MakeAvailable-Yes-green.svg)

## Installation
Fork my [release](https://github.com/joenahm/ws/tree/release) branch, then clone it to your computer.

> Add the path of this program to your environment variables list would be better !

## Usage
```
1. ws [website]

	example : ws github
	- to open github (which is in the record file already).

2. ws [website or search engine] [keywords]

	example : ws github MyLittleCPublicLibrary
	- do a search in github.
```
#### Management
```
-l : List all of the records.

-a -i <name> : Add site record.
-a -e <name> : Add searcher record.

-e -i <name> : Edit site record.
-e -e <name> : Edit searcher record.

-d -i <name> : Delete site record.
-d -e <name> : Delete searcher record.

-? : the "?" can be any thing else to call for this page.
```

## Remain to be done

1. MacOS Version
2. All 32bit Versions