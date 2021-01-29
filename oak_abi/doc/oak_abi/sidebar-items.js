initSidebarItems({"constant":[["INVALID_HANDLE","Invalid handle value."],["OAK_CHALLENGE",""],["OAK_LABEL_GRPC_METADATA_KEY","The key used for protobuf encoded Label in gRPC metadata."],["OAK_LABEL_HTTP_JSON_KEY","The HTTP header key used for JSON encoded Label in HTTP requests."],["OAK_LABEL_HTTP_PROTOBUF_KEY","The HTTP header key used for protobuf encoded Label in HTTP requests."],["OAK_SIGNED_CHALLENGE_GRPC_METADATA_KEY","The key used for protobuf encoded signed authentication challenge in gRPC metadata."],["OAK_SIGNED_CHALLENGE_HTTP_JSON_KEY","The HTTP header key used for JSON encoded signed authentication challenge."],["OAK_SIGNED_CHALLENGE_HTTP_PROTOBUF_KEY","The HTTP header key used for protobuf encoded signed authentication challenge."],["SPACE_BYTES_PER_HANDLE","Number of bytes needed per-handle for channel readiness notifications."]],"fn":[["channel_close","Closes the channel identified by `handle`."],["channel_create","Create a new unidirectional Channel."],["channel_create_with_downgrade","The same as `channel_create`, but also applies the current Node's downgrade privilege when checking IFC restrictions."],["channel_label_read","Returns the label for the channel identified by `handle`."],["channel_read","Read a message from a channel."],["channel_write","Write a message to a channel."],["channel_write_with_downgrade","The same as `channel_write`, but also applies the current Node's downgrade privilege when checking IFC restrictions."],["handle_clone","Create a new distinct handle to the same channel as `handle`."],["node_create","Creates a new Node instance running code identified by a serialized `NodeConfiguration`."],["node_create_with_downgrade","The same as `node_create`, but also applies the current Node's downgrade privilege when checking IFC restrictions."],["node_label_read","Returns the label of the current calling Node."],["node_privilege_read","Returns a label indicating the downgrade privilege of the current calling Node."],["random_get","Fill a buffer with random data."],["wait_on_channels","Wait for channels to be ready for reading."]],"mod":[["label","Labels represent the kinds of information that is allowed to be processed by entities in the Oak system. The Oak Runtime allows Oak Nodes to manipulate labels, and so the labels need to be passed across the Oak ABI in a defined binary format.  That format is a serialized protocol buffer holding the `Label` message defined in the label.proto file."],["proto",""]],"type":[["Handle","Handle used to identify read or write channel halves."],["NodeMain","Expected Rust type for a Node entrypoint."],["NodeMainC","Expected type for a Node entrypoint that is exposed as a Wasm export."]]});