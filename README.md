# compile

```sh
mkdir -p build
cd build
cmake ..
make
su -c "cp libPamela.so /lib64/security/pam_ela.so"
cd ..
su -c "echo '' >> /etc/pam.d/login"
```
