- 输入1:
  3 6 4 3 2
  2
  - 困难：要让cin自己停下来

	while (cin >> input[len++]) {
		char c = getchar();
		if (c == '\n') break;
	}
	
	cin >> num;
- 输入2：

(3,6)
(2,4)

困难：处理特殊符号

	char c;
	while (c = getchar()) {
		if (c == '(') {
			cin >> x1;
		}
		if (c == ',') {
			cin >> y1;
		}
		if (c == ')') {
			break;
		}
	}
	getchar();
	while (c = getchar()) {
		if (c == '(') {
			cin >> x2;
		}
		if (c == ',') {
			cin >> y2;
		}
		if (c == ')') {
			break;
		}
	}
- 输入3

[1,2,3,4,5]

困难：输入会特别特别常，不能用sstream转换流，直接getline好像溢出了

	while (c = getchar()) {
		if (c == '[' || c == ',') {
			cin >> input[len];
			len++;
		}
		else if (c == ']') {
			break;
		}
	}
- 输出到文件

```
#include<string>
#include<fstream>
#include<sstream>
string s;
getline(cin, s);
ofstream outfile("E:\\C++机考练习\\第一次作业\\Q34\\input.txt",ios::app);
outfile<<s<<endl;
outfile.close();
```



- 列表List类型删除，卧槽无情

```c++
list.remove_if([](auto& i) { return i > 10; });
```

- 迭代器删除

  ```c++
  list<int> lst{4, 1, 2, 3, 5};
  
  auto it = lst.begin();
  while (it != lst.end()){
      if((*it % 2) == 1){
          it = lst.erase(it);// erase and go to next
      } else{
          ++it;  // go to next
      }
  }
  
  for(auto it:lst)cout<<it<<" ";
  cout<<endl; 
  ```