#if OCCA_COI_ENABLED
#  ifndef OCCA_COI_HEADER
#  define OCCA_COI_HEADER

#include "occaBase.hpp"
#include "occaLibrary.hpp"

#include "occaKernelDefines.hpp"

#include "occaDefines.hpp"

#include <intel-coi/source/COIProcess_source.h>
#include <intel-coi/source/COIEngine_source.h>
#include <intel-coi/source/COIPipeline_source.h>
#include <intel-coi/source/COIEvent_source.h>
#include <intel-coi/source/COIBuffer_source.h>

namespace occa {
  typedef COIENGINE   coiDevice;
  typedef COIPROCESS  coiChief;   // Ruler of all threads

  typedef COIEVENT    coiEvent;

  typedef COIFUNCTION      coiKernel;
  typedef COIBUFFER        coiMemory;
  typedef COI_ACCESS_FLAGS coiMemoryFlags;

  typedef COIRESULT coiStatus;

  //---[ Data Structs ]---------------
  struct coiStream {
    COIPIPELINE handle;
    coiEvent lastEvent;
  };

  struct COIKernelData_t {
    coiChief chiefID;
    coiKernel kernel;

    // [-] Hard-coded for now
    coiMemory deviceArgv[50];
    coiMemoryFlags deviceFlags[50];

    char hostArgv[100 + 6*4 + 50*(4 + 8)];
    //            ^     ^      ^  ^   ^__[Max Bytes]
    // [Padding]__|     |      |  |__[Type]
    //                  |      |__[Maximum Args]
    //                  |__[KernelArgs]
  };

  struct COIDeviceData_t {
    coiDevice deviceID;
    coiChief chiefID;

    coiKernel kernelWrapper[50];
  };
  //==================================


  //---[ Helper Functions ]-----------
  namespace coi {
    void initDevice(COIENGINE &device, COIPROCESS &chief);

    occa::device wrapDevice(COIENGINE device);
  };
  //==================================


  //---[ Kernel ]---------------------
  template <>
  kernel_t<COI>::kernel_t();

  template <>
  kernel_t<COI>::kernel_t(const kernel_t &k);

  template <>
  kernel_t<COI>& kernel_t<COI>::operator = (const kernel_t<COI> &k);

  template <>
  kernel_t<COI>::kernel_t(const kernel_t<COI> &k);

  template <>
  std::string kernel_t<COI>::getCachedBinaryName(const std::string &filename,
                                                 kernelInfo &info_);

  template <>
  kernel_t<COI>* kernel_t<COI>::buildFromSource(const std::string &filename,
                                                const std::string &functionName_,
                                                const kernelInfo &info_);

  template <>
  kernel_t<COI>* kernel_t<COI>::buildFromBinary(const std::string &filename,
                                                const std::string &functionName_);

  template <>
  kernel_t<COI>* kernel_t<COI>::loadFromLibrary(const char *cache,
                                                const std::string &functionName_);

  template <>
  int kernel_t<COI>::preferredDimSize();

  template <>
  double kernel_t<COI>::timeTaken();

  template <>
  double kernel_t<COI>::timeTakenBetween(void *start, void *end);

  template <>
  void kernel_t<COI>::free();
  //==================================


  //---[ Memory ]---------------------
  template <>
  memory_t<COI>::memory_t();

  template <>
  memory_t<COI>::memory_t(const memory_t &m);

  template <>
  memory_t<COI>& memory_t<COI>::operator = (const memory_t &m);

  template <>
  void* memory_t<COI>::getMemoryHandle();

  template <>
  void* memory_t<COI>::getTextureHandle();

  template <>
  void memory_t<COI>::copyFrom(const void *source,
                               const uintptr_t bytes,
                               const uintptr_t offset);

  template <>
  void memory_t<COI>::copyFrom(const memory_v *source,
                               const uintptr_t bytes,
                               const uintptr_t destOffset,
                               const uintptr_t srcOffset);

  template <>
  void memory_t<COI>::copyTo(void *dest,
                             const uintptr_t bytes,
                             const uintptr_t offset);

  template <>
  void memory_t<COI>::copyTo(memory_v *dest,
                             const uintptr_t bytes,
                             const uintptr_t destOffset,
                             const uintptr_t srcOffset);

  template <>
  void memory_t<COI>::asyncCopyFrom(const void *source,
                                    const uintptr_t bytes,
                                    const uintptr_t destOffset);

  template <>
  void memory_t<COI>::asyncCopyFrom(const memory_v *source,
                                    const uintptr_t bytes,
                                    const uintptr_t srcOffset,
                                    const uintptr_t offset);

  template <>
  void memory_t<COI>::asyncCopyTo(void *dest,
                                  const uintptr_t bytes,
                                  const uintptr_t offset);

  template <>
  void memory_t<COI>::asyncCopyTo(memory_v *dest,
                                  const uintptr_t bytes,
                                  const uintptr_t destOffset,
                                  const uintptr_t srcOffset);

  template <>
  void memory_t<COI>::free();
  //==================================


  //---[ Device ]---------------------
  template <>
  device_t<COI>::device_t();

  template <>
  device_t<COI>::device_t(const device_t<COI> &k);

  template <>
  device_t<COI>& device_t<COI>::operator = (const device_t<COI> &k);

  template <>
  void device_t<COI>::setup(argInfoMap &aim);

  template <>
  deviceIdentifier device_t<COI>::getIdentifier() const;

  template <>
  void device_t<COI>::getEnvironmentVariables();

  template <>
  void device_t<COI>::appendAvailableDevices(std::vector<device> &dList);

  template <>
  void device_t<COI>::setCompiler(const std::string &compiler_);

  template <>
  void device_t<COI>::setCompilerEnvScript(const std::string &compilerEnvScript_);

  template <>
  void device_t<COI>::setCompilerFlags(const std::string &compilerFlags_);

  template <>
  std::string& device_t<COI>::getCompiler();

  template <>
  std::string& device_t<COI>::getCompilerEnvScript();

  template <>
  std::string& device_t<COI>::getCompilerFlags();

  template <>
  void device_t<COI>::flush();

  template <>
  void device_t<COI>::finish();

  template <>
  void device_t<COI>::waitFor(tag tag_);

  template <>
  stream device_t<COI>::createStream();

  template <>
  void device_t<COI>::freeStream(stream s);

  template <>
  stream device_t<COI>::wrapStream(void *handle_);

  template <>
  tag device_t<COI>::tagStream();

  template <>
  double device_t<COI>::timeBetween(const tag &startTag, const tag &endTag);

  template <>
  kernel_v* device_t<COI>::buildKernelFromSource(const std::string &filename,
                                                 const std::string &functionName_,
                                                 const kernelInfo &info_);

  template <>
  kernel_v* device_t<COI>::buildKernelFromBinary(const std::string &filename,
                                                 const std::string &functionName_);

  template <>
  void device_t<COI>::cacheKernelInLibrary(const std::string &filename,
                                           const std::string &functionName_,
                                           const kernelInfo &info_);

  template <>
  kernel_v* device_t<COI>::loadKernelFromLibrary(const char *cache,
                                                 const std::string &functionName_);

  template <>
  memory_v* device_t<COI>::wrapMemory(void *handle_,
                                      const uintptr_t bytes);

  template <>
  memory_v* device_t<COI>::wrapTexture(void *handle_,
                                       const int dim, const occa::dim &dims,
                                       occa::formatType type, const int permissions);

  template <>
  memory_v* device_t<COI>::malloc(const uintptr_t bytes,
                                  void *source);

  template <>
  memory_v* device_t<COI>::talloc(const int dim, const occa::dim &dims,
                                  void *source,
                                  occa::formatType type, const int permissions);

  template <>
  void device_t<COI>::free();

  template <>
  int device_t<COI>::simdWidth();
  //==================================

#include "operators/occaCOIFunctionPointerTypeDefs.hpp"
#include "operators/occaCOIKernelOperators.hpp"

  //---[ Error Handling ]-------------
  std::string coiError(coiStatus e);
  //==================================
};

#  endif
#endif
