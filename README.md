# vs-code-dev-base
Visual Studio container development environment for 3d / ML experimentation

## Notes
It's quite a specifc dev env image with these requirements
- Run on Nvidia cuda enabled machine
- Enable OpenGL from the image (forwarded to host)
- Primarily a c++ development environemnt
- Using cmake
- Using PyTorch C++ (with CUDA)
- Using OpenAI Gym (using zmq link in pytorch-cpp-rl)
- Planning on also experimenting with bullet engine as another 3d engine option.

## WIP
The useage of this repo with my other projects is very much still work in progress.
Not sure if I should build this as a docker base image which my other repo's can derive from? 

