AM_CXXFLAGS = $(PICKY_CXXFLAGS) -isystem $(srcdir)/../third_party/ -pthread
LDADD = -lm $(srcdir)/../third_party/gtest/libgtest.la

# Define unit tests
gtest_main_source = main.cc
TESTS = pifo_tests
check_PROGRAMS = $(TESTS)

# OMNeT++ tests
pifo_tests_SOURCES = $(gtest_main_source) pifo_tests.cc
