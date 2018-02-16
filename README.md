# EmbeddedAssessment
A repository for the implementation of an embedded assessment. 

# Protected Master branch

The repository has a protected master branch. Create a new branch and make a pull request to merge to master. Pull requests are only authorized to merge if they pass the CircleCI build and automated unit tests. 

# CircleCI integration. 
CircleCI integration uses Docker to set up an Ubuntu container. This Docker container is reused in CircleCI to recreate the build and carry out unit testing. 

# Building the ESP32 toolchain using Docker

## Export USER_UID
Before building you have to export your USER_UID:

  `export USER_UID=$UID;`

## Building the Container

Now build the container. This needs to be done only once. 

```bash
    docker-compose build
```

## Run the Container
To run it execute the command below. You can also add the -d parameter at the end to run it in the background. 

```bash
    docker-compose -f docker-compose.yml -f docker_compose_override/docker-compose.override.yml up -d
```

To stop the container, simply execute:

```bash
    docker-compose stop embedded_service
```


## Bashing into the container

To bash into the container execute the following command:

```bash
	docker exec -it embedded_service bash
```