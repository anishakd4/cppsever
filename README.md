# This a minimal webserver using c++

I have setup using ngnix and C++ but you can can ditch ngnix. I will mention steps for both.

# 1. Install boost library for async task and networking tasks

```
sudo apt install libboost-all-dev  # Ubuntu
brew install boost                 # macOS
```

# 2. Clone this code or repo at system.

# 3. build your project.

Ubuntu

```
g++ -o webserver webserver.cpp -lboost_system -lpthread
```

# 4. Now you can run the code

```
./webserver
```

# 5. Now hit this url in your browser

`http://localhost:8080/`

OR

if you don't want to hog up your terminal use

```
nohup ./webserver > output.log 2>&1 &
```
