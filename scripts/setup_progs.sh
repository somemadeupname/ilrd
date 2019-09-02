# Download and Install Chrome #
wget https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
sudo apt install ./google-chrome-stable_current_amd64.deb

# Download and Install Slack #
wget https://downloads.slack-edge.com/linux_releases/slack-desktop-3.3.8-amd64.deb
sudo apt install ./slack-desktop-*.deb

# Install Gnome Tweaks Tool #
sudo apt install gnome-tweak-tool

# Increase text size #
gsettings set org.gnome.desktop.interface text-scaling-factor 1.2

# Gedit plugins
sudo apt-get update
sudo apt-get install gedit-plugins

#background
wget http://wallpapershdnow.com/images/tv-shows/animation/rick-and-morty/rick-and-morty-background-10.jpg -o ~/Pictures/rnm.jpg

# Blueman if QCII doesn't work #
Install blueman
sudo apt install blueman
# Delete the paired device in the bluetooth settings.
sudo pkill pulseaudio
sudo /etc/init.d/bluetooth restart
# Turn off headphones.
# Turn on headphones, and press green/go until headphones notification voice says
# "Ready to pair."
# Launch blueman, and from the upper right menu, right-click the icon to bring
# up the blueman menu. Select Setup new device.
# Pair the device, and when you are given an option, not headphones,
# not handsfree. Use the Audio sink option.
# Then when you look into the audio settings panel,
# the device should be displayed.


# Frippery Move Clock - install from Ubuntu Software #
