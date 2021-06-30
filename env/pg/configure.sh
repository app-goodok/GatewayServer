# prepare new user
sudo -u postgres psql -c "ALTER USER postgres PASSWORD '123';"
psql -U postgres -h localhost -c "CREATE USER worker with PASSWORD '123';"
psql -U postgres -h localhost -c "CREATE DATABASE chat;"
psql -U postgres -h localhost -c "GRANT ALL PRIVILEGES ON DATABASE chat TO worker;"

# configure Db
psql -U worker -h localhost -d chat "CREATE TABLE IF NOT EXISTS clients(client_id serial primary key, login varchar(32), password varchar(32));"
psql -U worker -h localhost -d chat "CREATE TABLE channels(channel_id serial primary key, channel_name varchar(32));"

psql -U worker -h localhost -d chat "CREATE TABLE subscriptions(client_id integer references clients(client_id), channel_id integer references channels(channel_id));"
psql -U worker -h localhost -d chat "CREATE TABLE history(client_id integer references clients(client_id), channel_id integer references channels(channel_id), datetime timestamp, message varchar(255));"
