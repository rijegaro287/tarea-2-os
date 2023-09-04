clear
cmake .
make

sudo chmod +x ./build/ImageServer
sudo mkdir -p /home/$USER/Documents/ImageServer
sudo cp ./build/ImageServer /home/$USER/Documents/ImageServer/ImageServer

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