#include "gmock/gmock.h"

#ifdef __clang__
extern "C" {
int __llvm_profile_runtime = 0;
}

extern "C" {
void __llvm_profile_initialize_file(void);
void __llvm_profile_set_filename(char *);
int __llvm_profile_write_file(void);
}
#endif

int main(int argc, char **argv) {
#ifdef __clang__
  __llvm_profile_initialize_file();
#endif

  ::testing::InitGoogleTest(&argc, argv);

  int rc = RUN_ALL_TESTS();

#ifdef __clang__
  __llvm_profile_write_file();
#endif

  return rc;
}
