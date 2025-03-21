# This a minimal webserver using c++

I have setup using ngnix and C++ but you can can ditch ngnix at my aws instance.

## Firstly we will run this at our personal PC and verify if all works and then we wil move to deploy it to a public server.

### 1. Install boost library for async task and networking tasks

```
sudo apt install libboost-all-dev  # Ubuntu
brew install boost                 # macOS
```

### 2. Clone this code or repo at system.

### 3. build your project.

Ubuntu

```
g++ -o webserver webserver.cpp -lboost_system -lpthread
```

MAC

```
g++ -o webserver webserver.cpp -std=c++20 -Wall -Wextra -g -I/opt/homebrew/opt/boost/include -pthread -L/opt/homebrew/opt/boost/lib -lboost_system -lboost_system -lboost_thread
```

### 4. Now you can run the code

```
./webserver
```

### 5. Now hit this url in your browser

`http://localhost:8080/`

Now Nothing is complete if you can't connect it from any public ip. SO we will deploy it to public server. Now here I am using a Amazon aws ec2 instance with Ubuntu 24 installed. You are free to choose any public server.

### 1. Install boost library for async task and networking tasks

```
sudo apt install libboost-all-dev  # Ubuntu
```

### 2. Clone this code or repo at system.

### 3. build your project.

Ubuntu

```
g++ -o webserver webserver.cpp -lboost_system -lpthread
```

MAC

```
g++ -o webserver webserver.cpp -std=c++20 -Wall -Wextra -g -I/opt/homebrew/opt/boost/include -pthread -L/opt/homebrew/opt/boost/lib -lboost_system -lboost_system -lboost_thread
```

### 4. Now you can run the code. Here we are using nohup so that our webserver keeps running even after terminal is closed.

```
nohup ./webserver > output.log 2>&1 &

```

### 5. Now our webserver is running at port 80. We can verify via wget command at our terminal.

```
wget http://localhost:8080/
```

We can see our process running via

```
ps aux | grep webserver
```

We can use this command to close the webserver if needed.

```
kill -9 <PID>
```

### 6. Install ngnix

```
sudo apt install nginx
```

then edit /etc/nginx/sites-available/default to below content:

```
server {
	listen 80 default_server;
	listen [::]:80 default_server;

	location / {
        proxy_pass http://127.0.0.1:8080;
    }
}
```

### 7. Now please open port 80 frm the public server where you performed the above steps. And then lets suppose if your server public ip is 192.169.1.89 , the hit

http://192.169.1.89:80

### 8. Now if your server reboots for some reason, then your webserver won't be running anymore. To ensure your C++ web server (nohup ./webserver > output.log 2>&1 &) starts automatically after a reboot, you can use crontab.

```
crontab -e
```

Add this line at the end. Here you have to share the full path of your webserver executable.

```
@reboot nohup /home/ubuntu/webserver > /home/ubuntu/output.log 2>&1 &
```

### 9. You can check access logs to your server

```
sudo tail -f /var/log/nginx/access.log
```

## Finally your system is ready. Again to use https you can use Certbot (Let’s Encrypt). But for these steps you need to have a domain pointing to your ngnix configuration that is your public server.

### 1. Replace your-domain.com with your actual domain.

```
sudo apt install -y certbot python3-certbot-nginx
sudo certbot --nginx -d your-domain.com -d www.your-domain.com
```

### 2.Check your Nginx configuration:

```
sudo nginx -t
```

If valid, restart Nginx:

```
sudo systemctl restart nginx
```
