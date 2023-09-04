clear
cmake .
make

sudo rm -rf /home/$USER/Documents/ImageServer
sudo mkdir -p /home/$USER/Documents/ImageServer
sudo cp ./build/ImageServer /home/$USER/Documents/ImageServer/ImageServer
sudo cp ./config.conf /home/$USER/Documents/ImageServer/config.conf
sudo chmod 777 -R /home/$USER/Documents/ImageServer

sudo touch /home/$USER/Documents/ImageServer/run.sh
sudo chmod 777 /home/$USER/Documents/ImageServer/run.sh
sudo echo "#!/bin/bash
cd /home/$USER/Documents/ImageServer
sudo ./ImageServer" > /home/$USER/Documents/ImageServer/run.sh

touch ImageServer.service
echo "[Unit]
Description=ImageServer Service
After=network.target

[Service]
ExecStart=/home/$USER/Documents/ImageServer/run.sh
Restart=always

[Install]
WantedBy=multi-user.target" > ImageServer.service

sudo rm -rf /etc/systemd/system/ImageServer.service

sudo cp ./ImageServer.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable ImageServer