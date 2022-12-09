# 实验四报告

姓名：牟真伟			学号：PB20051061

------

## 实验内容

### TCP

TCP连接建立时三次握手的数据包:

![image-20221208153552477](https://gitee.com/aweary/img/raw/master/img/202212081535595.png)

TCP连接释放时的数据包(只有三次挥手):

![image-20221208154011773](https://gitee.com/aweary/img/raw/master/img/202212081540837.png)

| 项目                 | 数据                |
| -------------------- | ------------------- |
| 发送方IP地址和端口号 | 192.168.43.177:6776 |
| 接收方IP地址和端口号 | 93.184.216.34:80    |

| 项目  | 握手包1 | 握手包2 | 握手包3 | 释放包1 | 释放包2 | 释放包3 |
| ----- | ------- | ------- | ------- | ------- | ------- | ------- |
| Seq号 | 0       | 0       | 1       | 80      | 1613    | 81      |
| Ack号 | 无      | 1       | 1       | 1613    | 81      | 1614    |
| Flags | SYN     | SYN,ACK | ACK     | FIN,ACK | FIN,ACK | ACK     |

### HTTP/HTTPS

`curl -4 -v http://www.example.com` HTTP数据包:

![image-20221208162529777](https://gitee.com/aweary/img/raw/master/img/202212081625809.png)

`curl -4 -v -d "user=test" http://example.com/login`HTTP数据包:

![image-20221208162708514](https://gitee.com/aweary/img/raw/master/img/202212081627542.png)

| 指令                                                 | 协议版本 | 方法类型 | 状态码 | 回复包内容类型 |
| ---------------------------------------------------- | -------- | -------- | ------ | -------------- |
| `curl -4 -v http://www.example.com`                  | HTTP/1.1 | GET      | 200    | text/html      |
| `curl -4 -v -d "user=test" http://example.com/login` | HTTP/1.1 | POST     | 404    | text/html      |

`curl -4 -v https://www.example.com`HTTPS数据包:

![https3](https://gitee.com/aweary/img/raw/master/img/202212082348879.png)

### DNS

| 查询目标                              | 命令                                  | 结果 |
| ------------------------------------- | ------------------------------------- | ---- |
| www.baidu.com 的 IPv4 地址            | `dig www.baidu.com @8.8.8.8`          | 14.215.177.39或14.215.177.38 |
| 202.38.75.11 的域名                   | `dig -x 202.38.75.11 @8.8.8.8` | infonet.ustc.edu.cn |
| jw.ustc.edu.cn 的 IPv6 地址（AAAA）   | `dig -t aaaa jw.ustc.edu.cn @8.8.8.8`        | 2001:da8:d800:642::248 |
| mail.ustc.edu.cn 的邮件交换记录（MX） | dig mx mail.ustc.edu.cn @8.8.8.8 | 5 smtp1.ustc.edu.cn,10 smtp.ustc.edu.cn,10 smtp2.ustc.edu.cn |
| i.ustc.edu.cn 的别名记录（CNAME） | dig cname i.ustc.edu.cn @8.8.8.8 | revproxy.ustc.edu.cn |
| example.com 的域名服务器记录（NS）      | dig ns example.com @8.8.8.8 | a.iana-servers.net,b.iana-servers.net |

dig查询根服务器:

![image-20221208203253918](https://gitee.com/aweary/img/raw/master/img/202212082032999.png)

`dig`查询`<your-student-id>.ustc.edu.cn` :

![dig](https://gitee.com/aweary/img/raw/master/img/202212082348405.png)

status字段为NXDOMAIN

### FTP

主动模式:

![active](https://gitee.com/aweary/img/raw/master/img/202212082346177.png)

客户端开启的数据通道的端口号为192*256+151=49303

被动模式:

![passive](https://gitee.com/aweary/img/raw/master/img/202212082347928.png)

服务端开启的数据端口的端口号为181*256+105=46441,与后续数据包一致

![data](https://gitee.com/aweary/img/raw/master/img/202212082347215.png)

## 思考题

#### 1. 解释 HTTP 中的幂等是什么意思？GET 操作是幂等的吗？POST 呢？

​	HTTP方法的幂等性是指一次和多次请求某一个资源应该具有同样的副作用,GET方法只是获取特定资源,并不会对该资源做出修改,因此GET操作是幂等的.

POST方法会对资源做出修改,调用多次POST方法得到的结果不同,因此POST方法不是幂等的.

#### 2. HTTPS 抓到的数据包与之前 HTTP 中抓到的有何不同？这是什么原因导致的？

HTTPS抓到的数据包使用TLS协议传输,且传输的数据为加密后的数据,因为HTTPS运行在SSL/TLS上,会对传输的数据进行加密.

#### 3. FTP 实验中使用的 `sudo tcpdump -i any -vvnX host home.ustc.edu.cn` 指令整体可以达到什么效果？其中每个参数的含义分别是什么？

在所有网络接口上,抓取ip地址为home.ustc.edu.cn对应地址的数据包,并输出详细的报文信息

`-i any`:监听所有端口

`host`:抓取ip地址为home.ustc.edu.cn对应地址的数据包

`-vv`:输出详细的报文信息

`-n`:不把网络地址转换成名字

`-X`:以16进制和ASCII码形式显示每个报文（去掉链路层报头）

#### 4. 解释从输入网址，到浏览器显示网页，在客户端的应用层依次发生了什么？

​	应用层首先发起DNS请求,查询到输入网址域名所对应的IP地址,应用层的HTTP协议对输入网址的资源发出HTTP请求,服务器处理请求并返回HTTP响应报文,得到服务器端的资源文件后,浏览器将资源文件渲染成网页,并显示出来.