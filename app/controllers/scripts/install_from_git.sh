#!/bin/bash

#run as oaz
APP_DIR="/var/www/html/oneandzeroWeb"
cd $APP_DIR
git pull origin master
chown www-data:www-data tmp
chown -R oaz:oaz db
chown www-data:www-data log
sudo -i -u oaz bash -c "cd $APP_DIR; bundle install"
sudo -i -u oaz bash -c "cd $APP_DIR; rake db:migrate RAILS_ENV=development"
chown -R www-data:www-data db
