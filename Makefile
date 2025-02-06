
GIT_COMMIT_HASH=$(shell git rev-parse --short HEAD)

debug:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		../.. \
	&& \
	make -j 8

debugTests:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-DENABLE_TESTS=ON \
		../.. \
	&& \
	make -j 8

release:
	mkdir -p cmake-build/Release && cd cmake-build/Release && cmake -DCMAKE_BUILD_TYPE=Release ../.. && make -j 8

clean:
	rm -rf cmake-build

cleanSandbox:
	rm -rf sandbox

copyRelease:
	rsync -avH cmake-build/Release/lib cmake-build/Release/bin sandbox/

copyDebug:
	rsync -avH cmake-build/Debug/lib cmake-build/Debug/bin sandbox/

copy:
	mkdir -p sandbox/
	rsync -avH data sandbox/
	mv sandbox/data/*.sh sandbox/

sandbox: release copy copyRelease

sandboxDebug: debug copy copyDebug

sandboxTests: debugTests copy copyDebug

runserver: sandbox
	cd sandbox && ./run.sh server

drunserver: sandboxDebug
	cd sandbox && ./debug.sh server

docker:
	docker build \
		--build-arg GIT_COMMIT_HASH=${GIT_COMMIT_HASH} \
		--tag totocorpsoftwareinc/tcp-server:${GIT_COMMIT_HASH} \
		-f build/tcp-server/Dockerfile \
		.