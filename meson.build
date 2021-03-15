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

# # begin protobuf: https://developers.google.com/protocol-buffers/
# # protobuf: must be installed independently and has to be found...
# protoc = find_program('protoc', required : true)
# protobuf_dep = dependency('protobuf', required : true)

# gen = generator(protoc, \
#   output    : ['@BASENAME@.pb.cc', '@BASENAME@.pb.h'],
#   arguments : ['--proto_path=@CURRENT_SOURCE_DIR@/src', '--cpp_out=@BUILD_DIR@', '@PLAINNAME@'])

# # change proto file accordingly
# generated = gen.process('src/dummy.proto')
# # end protobuf

inc_dir_server = include_directories('server/include')
src_server = ['server/src/main.cpp', 'server/src/bullet.cpp', 'server/src/robot.cpp', 'server/src/window.cpp']
#protobuf: src = ['src/main.cpp', generated]

inc_dir_client = include_directories('client/include')
src_client = ['client/src/main.cpp']

graphics = dependency('sfml-graphics')
window = dependency('sfml-window')

executable('robo-server',
           sources : src_server,
           include_directories : inc_dir_server,
#           dependencies : [thread_dep, protobuf_dep]
           dependencies : [thread_dep, graphics, window]
)

executable('robo-client',
           sources : src_client,
           include_directories : [inc_dir_client,inc_dir_server],
           dependencies : [thread_dep, graphics, window]
)