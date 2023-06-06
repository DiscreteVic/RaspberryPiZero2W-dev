sudo apt-get install -y pkg-config libjaylink-dev gcc-arm-none-eabi automake autoconf build-essential texinfo libtool libftdi-dev libusb-1.0-0-dev

sudo cp ~/shared/env/remote-dirs /usr/local/bin/.
sudo chmod 777 /usr/local/bin/remote-dirs 

mkdir ~/zero2w
cd ~/zero2w
git clone https://review.openocd.org/openocd/
# USUALLY FAIS RUN IT MANUALLY
#./bootstrap
#./configure --enable-ftdi --enable-sysfsgpio --enable-bcm2837gpio --enable-jlink
#
#make 
#sudo make install