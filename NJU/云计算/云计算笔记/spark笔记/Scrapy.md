# Scrapy

- 做三件事
  - 打开页面
  - 提取数据
  - 保存数据

### 打开页面

- 发送请求：
  - (scrapy spider必须的常量) start_urls
- 处理返回：
  - `yield scrapy.Request(url=url, callback=self.parse)`说的是，我们需要写一个callback方法来处理response: **<u>parse(response)</u>**

### 提取数据

- ```response.css(".page-navigator a::attr(href)").extract()```
  - ' . '对应class, ' # '对应id, ' :: '对应标签<>里面的属性 标签名::attr(属性名)，关键是如何缩小范围
  - 特别一点 ::text 提取文字
- 还有很多高级的css选择器，总之可以应对90%问题
- xpath
  - 标签[@属性名=“属性值”]
  - //ol[@class="page-navigator"]//@href
  - extract()一般是把data给拿出来
  - //title//text()返回文本
  - 例子：response.xpath("//ul[@class='tags-list']//a//text()").extract()











## scrapy命令行

- 全局命令
  - scrapy startproject myScrapy
  - genspider 帮助创建爬虫模板
  - settings 通常不用
  - runspider 基于文件运行（如果不想创建项目）
    - scrapy runspider scrapy_cn.py
  - shell 主要用于调试，看看选择器做的对不对，这个比较重要
    - scrapy shell http://www.xxxxxxxxx
  - fetch,view用于异步传输的排错，我不太懂
  - version
- 在某个特定文件夹下打开cmd
  - 右键选中文件夹，按着shift，再右键打开，快捷键S对应的就是在命令行打开
- 项目命令
  - scrapy crawl scrapyd_cn
  - check 检查现在在爬的蜘蛛
  - list 显示有多少蜘蛛：spider文件夹下的xx.py文件中定义的name