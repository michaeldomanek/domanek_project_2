# uncomment as necessary
project('RobotGame', 'cpp',
        license : ['Boost'],
        version : '0.1.1',
        default_options : ['cpp_std=c++17', 'warning_level=3', 'werror=true'])

thread_dep = dependency('threads')

# begin asio: https://think-async.com/Asio/
add_global_arguments('-I' + get_option('asio_include_dir'), language : 'cpp')
add_global_arguments('-DASIO_STANDALONE', language : 'cpp')
add_global_arguments('-DASIO_NO_DEPRECATED', language : 'cpp')
# end asio

# CLI11: https://github.com/CLIUtils/CLI11
add_global_arguments('-I' + get_option('cli11_include_dir'), language : 'cpp')

# spdlog: https://github.com/gabime/spdlog
add_global_arguments('-I' + get_option('spdlog_include_dir'), language : 'cpp')

# begin protobuf: https://developers.google.com/protocol-buffers/
protoc = find_program('protoc', required : true)
protobuf_dep = dependency('protobuf', required : true)

gen = generator(protoc, \
  output    : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h'],
  arguments : ['--proto_path=@CURRENT_SOURCE_DIR@/src/messages/', '--cpp_out=@BUILD_DIR@', '@PLAINNAME@'])

generated = gen.process('src/messages/robotProperties.proto')
# end protobuf

# begin grpc: https://grpc.io/
grpc_cpp_dep = dependency('grpc++', required : true)
grpc_plugin = find_program('grpc_cpp_plugin', required : true)

gen_grpc = generator(protoc, \
  output    : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h', '@BASENAME@.grpc.pb.cc', '@BASENAME@.grpc.pb.h'],
  arguments : ['--proto_path=@CURRENT_SOURCE_DIR@/src/messages/', '--grpc_out=@BUILD_DIR@', '--cpp_out=@BUILD_DIR@',  '@PLAINNAME@', 
               '--plugin=protoc-gen-grpc=' + grpc_plugin.path()]
)

grpc_generated = gen_grpc.process('src/messages/robotServer.proto')
#end grpc

inc_dir = include_directories('include')

src_server = ['src/server_src/main.cpp', 'src/server_src/bullet.cpp', 
              'src/server_src/robot.cpp', 'src/server_src/window.cpp',
              'src/server_src/grpcServer.cpp', generated, grpc_generated]

src_client = ['src/client_src/main.cpp', 'src/client_src/grpcClient.cpp', generated, grpc_generated]

graphics = dependency('sfml-graphics')
window = dependency('sfml-window')

executable('robo-server',
           sources : src_server,
           include_directories : inc_dir,
           dependencies : [thread_dep, graphics, window, protobuf_dep, grpc_cpp_dep]
)

executable('robo-client',
           sources : src_client,
           include_directories : inc_dir,
           dependencies : [thread_dep, graphics, window, protobuf_dep, grpc_cpp_dep]
)