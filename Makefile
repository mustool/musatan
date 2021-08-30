BUNDLE = lv2pftci-musatan.lv2
INSTALL_DIR = /usr/local/lib/lv2

$(BUNDLE): manifest.ttl musatan.ttl musatan.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl musatan.ttl musatan.so $(BUNDLE)

musatan.so: musatan.cpp
	g++ -shared -fPIC -DPIC musatan.cpp `pkg-config --cflags --libs lv2-plugin` -o musatan.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) musatan.so
