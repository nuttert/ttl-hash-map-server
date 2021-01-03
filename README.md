# ttl-hash-map-server
![image](https://github.com/nuttert/ttl-hash-map-server/blob/master/readme_images/schema_.png)
## Build
`docker-compose up --build`
## Run Server
`docker-compose run --rm l1_memory_cache`

`make run`
## Run client
`netcat localhost 9099`

## Commands examples
- SET, KEYS

`SET {"a": ["a", "b", "c"]}`

`KEYS`
#### Output:
`["a"]`
______
- GET, DEL

`GET "a"`
#### Output:
`["a", "b", "c"]`
_______
`DEL "a"`
`GET "a"`
#### Output:
"null"
______
