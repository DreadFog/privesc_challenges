### Grafana data is stored in /var/lib/docker/grafana-storage

#### execution:
``` 
docker run -d -p3000:3000 --name=grafana -v grafana-storage:/var/lib/grafana grafana/grafana:latest
```
#### admin password set:
```
7pKhJ8!7pV
```

#### Underprivileged user:
```
user: underprivileged
password: underprivileged
```
