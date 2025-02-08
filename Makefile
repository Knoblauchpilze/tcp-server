
GIT_COMMIT_HASH=$(shell git rev-parse --short HEAD)

debug:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		../.. \
	&& \
	make -j 8

debugWithTests:
	mkdir -p cmake-build/Debug && \
	cd cmake-build/Debug && \
	cmake \
		-DCMAKE_BUILD_TYPE=Debug \
		-DENABLE_TESTS=ON \
		../.. \
	&& \
	make -j 8

release:
	mkdir -p cmake-build/Release && \
	cd cmake-build/Release && \
	cmake \
		-DCMAKE_BUILD_TYPE=Release \
		../.. \
	&& \
	make -j 8

clean:
	rm -rf cmake-build

cleanSandbox:
	rm -rf sandbox

copyData:
	mkdir -p sandbox/
	rsync -avH data sandbox/
	mv sandbox/data/*.sh sandbox/

copyDebug: debug copyData
	rsync -avH cmake-build/Debug/lib cmake-build/Debug/bin sandbox/

copyRelease: release copyData
	rsync -avH cmake-build/Release/lib cmake-build/Release/bin sandbox/

runserver: copyRelease
	cd sandbox && ./run.sh server 2323

drunserver: copyDebug
	cd sandbox && ./debug.sh server 2323

# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
PHONY: .tests
tests: debugWithTests copyDebug

docker:
	docker build \
		--build-arg GIT_COMMIT_HASH=${GIT_COMMIT_HASH} \
		--tag totocorpsoftwareinc/tcp-server:${GIT_COMMIT_HASH} \
		-f build/tcp-server/Dockerfile \
		.

docker-no-cache:
	docker build \
		--no-cache \
		--build-arg GIT_COMMIT_HASH=${GIT_COMMIT_HASH} \
		--tag totocorpsoftwareinc/tcp-server:${GIT_COMMIT_HASH} \
		-f build/tcp-server/Dockerfile \
		.