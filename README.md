hdebug
======

huborg_debug.so module outputs each compiled php5 script into syslog

not as verbose as trace from xdebug

======
sudo apt-get install php5-dev

extract to directory

phpize

./configure

make install

Add "extension=huborg_debug.so" to php.ini
