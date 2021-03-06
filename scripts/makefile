#---[ Paths ]-------------------------------------
oPath = obj
sPath = src
iPath = include
#=================================================


#---[ Default Variables ]-------------------------
Debug_Enabled  = 0
Check_Enabled  = 1

usingICPC      = 0
OpenGL_Enabled = 0

openclEnabled   = 0
openmpEnabled   = 0
cudaEnabled     = 0
coiEnabled      = 0
pthreadsEnabled = 0

ifdef OCCA_DEVELOPER
 ifeq ($(OCCA_DEVELOPER), 1)
  ifeq ($(DEBUG), 0)
     Debug_Enabled = 0
  else
     Debug_Enabled = 1
  endif
 else
  ifeq ($(DEBUG), 1)
     Debug_Enabled = 1
  else
     Debug_Enabled = 0
  endif
 endif
endif

ifndef CXX
	CXX = g++
endif

ifndef FC
	FC = gfortran
endif

ifndef CXXFLAGS
	ifeq ($(DEBUG), 1)
		CXXFLAGS = -g
	else
		CXXFLAGS = -O3
	endif
endif

ifndef FCFLAGS
	ifeq ($(DEBUG), 1)
		FCFLAGS = -g
	else
		FCFLAGS = -O3
	endif
endif

compiler      = $(CXX)
compilerFlags = $(CXXFLAGS)

Fcompiler      = $(FC)
FcompilerFlags = $(FCFLAGS)
#=================================================


#---[ Paths/Flags/Links ]-------------------------
paths  = -I./$(sPath) -I./$(iPath) -I${OCCA_DIR}/lib -I${OCCA_DIR}/include
paths += -I/sw/include/ -I/opt/AMDAPP/include/ -I/usr/include/ -I/opt/X11/include
paths += -I/Developer/NVIDIA/CUDA-5.5/include/ -I/usr/local/cuda/include -I/glb/data/comp_mod/Tools/cuda-5.5/include
paths += -L/opt/X11/lib -L${OCCA_DIR}/lib -L/usr/local/cuda/lib64 -L/usr/local/cuda/lib -L/usr/lib
paths += $(foreach path, $(subst :, ,$(OCCA_INCLUDE_PATH)), -I$(path))
paths += $(foreach path, $(subst :, ,$(OCCA_LIBRARY_PATH)), -L$(path))

flags = -Wno-deprecated

links = -locca
#=================================================


#---[ OS Detection ]------------------------------
LINUX_OS   = 1
OSX_OS     = 2
WINDOWS_OS = 4

flags += -D LINUX_OS=$(LINUX_OS) -D OSX_OS=$(OSX_OS) -D WINDOWS_OS=$(WINDOWS_OS)

ifdef SystemRoot
	OS = WINDOWS
else
ifeq ($(shell uname -s),Darwin)
	OS = OSX
else
	OS = LINUX
endif
endif
#=================================================


#---[ OS-Based Dependencies ]---------------------
ifeq ($(usingICPC), 1)
	Debug_Flags      = -g
	Release_Flags    = -ldl -no-ansi-alias -funroll-all-loops -fp-model fast=2 -ftz -O3 -xHost
	FcompilerModFlag = -module
else
	Debug_Flags      = -g
	Release_Flags    = -msse -O3 -ftree-vectorize -funroll-all-loops -ffast-math -Wno-unused-value
	FcompilerModFlag = -J
endif

ifeq ($(OS),OSX)
	flags       += -D OCCA_OS=OSX_OS
	OpenGL_Flags =
	OpenCL_Flags =
	CUDA_Flags   =
	COI_Flags    =

	links       += -framework accelerate -framework CoreServices
	OpenGL_Links = -D GL_GLEXT_PROTOTYPES -framework OpenGL -lX11 -lGL
	OpenCL_Links = -framework OpenCL
	CUDA_Links   = -framework CUDA
	COI_Links    =
endif

ifeq ($(OS),LINUX)
	flags        += -D OCCA_OS=LINUX_OS
	OpenGL_Flags  = -D GL_GLEXT_PROTOTYPES
	OpenCL_Flags  =
	CUDA_Flags    =
	COI_Flags     =

	links        += -lm -lrt -ldl
	OpenGL_Links  =  -L/usr/lib/fglrx/ -lGL -lX11
	OpenCL_Links  = -lOpenCL
	CUDA_Links    = -lcuda
	COI_Links     = -lcoi_host
endif

ifeq ($(OS),WINDOWS)
	flags        += -D OCCA_OS=WINDOWS_OS
	OpenGL_Flags  =
	OpenCL_Flags  =
	CUDA_Flags    =
	COI_Flags     =

	links        +=
	OpenGL_Links  =
	OpenCL_Links  =
	CUDA_Links    =
	COI_Links     =
endif
#=================================================


#---[ Variable Dependencies ]---------------------
ifdef OCCA_PTHREADS_ENABLED
	Pthreads_Enabled = $(OCCA_PTHREADS_ENABLED)
else
	Pthreads_Enabled = pthreadsEnabled
endif

ifdef OCCA_OPENMP_ENABLED
	OpenMP_Enabled = $(OCCA_OPENMP_ENABLED)
ifeq ($(OCCA_OPENMP_ENABLED),1)
	links += -fopenmp
endif
else
	OpenMP_Enabled = openmpEnabled
endif

ifdef OCCA_OPENCL_ENABLED
	OpenCL_Enabled = $(OCCA_OPENCL_ENABLED)
else
	OpenCL_Enabled = openclEnabled
endif

ifdef OCCA_CUDA_ENABLED
	CUDA_Enabled = $(OCCA_CUDA_ENABLED)
else
	CUDA_Enabled = cudaEnabled
endif

ifdef OCCA_COI_ENABLED
	COI_Enabled = $(OCCA_COI_ENABLED)
else
	COI_Enabled = coiEnabled
endif

ifeq ($(Debug_Enabled), 1)
	flags += $(Debug_Flags)   -DOCCA_DEBUG_ENABLED=1
else
	flags += $(Release_Flags) -DOCCA_DEBUG_ENABLED=0 -DNDEBUG=1 -DOCCA_SHOW_WARNINGS=0
endif

ifeq ($(OpenMP_Enabled), 1)
	flags += -fopenmp -DOCCA_OPENMP_ENABLED=1
else
	flags +=          -DOCCA_OPENMP_ENABLED=0
endif

ifeq ($(Check_Enabled), 1)
	flags += -DOCCA_CHECK_ENABLED=1
else
	flags += -DOCCA_CHECK_ENABLED=0
endif

ifeq ($(Pthreads_Enabled), 1)
	flags += -DOCCA_PTHREADS_ENABLED=1
else
	flags += -DOCCA_PTHREADS_ENABLED=0
endif

ifeq ($(OpenGL_Enabled), 1)
	flags += $(OpenGL_Flags) -DOCCA_OPENGL_ENABLED=1
	links += $(OpenGL_Links)
else
	flags +=                 -DOCCA_OPENGL_ENABLED=0
endif


ifeq ($(OpenCL_Enabled), 1)
	flags += $(OpenCL_Flags) -DOCCA_OPENCL_ENABLED=1
	links += $(OpenCL_Links)
else
	flags +=                 -DOCCA_OPENCL_ENABLED=0
endif


ifeq ($(CUDA_Enabled), 1)
	flags += $(CUDA_Flags) -DOCCA_CUDA_ENABLED=1
	links += $(CUDA_Links)
else
	flags +=               -DOCCA_CUDA_ENABLED=0
endif

ifeq ($(COI_Enabled), 1)
	flags += $(COI_Flags) -DOCCA_COI_ENABLED=1
	links += $(COI_Links)
else
	flags += -DOCCA_COI_ENABLED=0
endif
#=================================================
