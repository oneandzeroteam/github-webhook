#!/bin/bash

#run as oaz
APP_DIR="/var/www/html/oneandzeroWeb"
cd $APP_DIR
git pull origin master
chown -R oaz:oaz db tmp log
sudo -i -u oaz bash -c "cd $APP_DIR; bundle install"
sudo -i -u oaz bash -c "cd $APP_DIR; DISABLE_DATABASE_ENVIRONMENT_CHECK=1  rake db:drop RAILS_ENV=production"
sudo -i -u oaz bash -c "cd $APP_DIR; rake db:migrate RAILS_ENV=production"
sudo -i -u oaz bash -c "cd $APP_DIR; rake db:seed RAILS_ENV=production"
chown -R www-data:www-data db tmp log

chown -R oaz:oaz public
sudo -i -u oaz bash -c "cd $APP_DIR; RAILS_ENV=production rake assets:clean assets:precompile"
chown -R root:root public
