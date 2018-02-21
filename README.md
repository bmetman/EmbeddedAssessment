# EmbeddedAssessment
A repository for the implementation of an embedded assessment. 

# Protected Master branch

The repository has a protected master branch. Create a new branch and make a pull request to merge to master. Pull requests are only authorized to merge if they pass the CircleCI build and automated unit tests. 

# CircleCI integration. 
CircleCI integration uses Docker to set up an Ubuntu container. This Docker container is reused in CircleCI to recreate the build and carry out unit testing. This ensures a clean container to run the code in and do unit testing, keeping track of all the dependencies. The circleci configuration can be found in the .circle/config.yml file. Automatic memory leak checks are also implemented using ValGrind. 

# Mocked parts
Much of the hardware interaction is mocked. Two major features missing at the moment are the TCP interaction and the file storage. The TCP interaction is now mocked both by the client and the server. The file storage, used by the server, would allow for perpetual data storage. Both weren't implemented due time constraints, but the scaffolding is there. Also, a simpler request client is missing (which would request sensor data from the server) but its calls are mocked by the server and unit tested. 
