/* 
 * File:   Test_OSExec.cpp
 * Author: mbai
 * 
 * Created on August 3, 2015, 9:41 AM
 */

#include "test_os_exec.h"

Test_os_exec::Test_os_exec()
{
}


Test_os_exec::~Test_os_exec()
{
}



TEST_F(Test_os_exec, echo_args) 
{
    
    lib_exec_arg_t args {(char *)"abcd", NULL};

    Libos_exec task("/bin/echo", args);
    
    ASSERT_EQ(0, task.init());    
    ASSERT_EQ(0, task.run());
    
    lib_exec_buf_t buffer;
    lib_exec_buf_t expected = {'a', 'b', 'c', 'd', '\n'};
    
    ASSERT_EQ(0, task.get_std_out(buffer));

    ASSERT_EQ(expected, buffer);
}

TEST_F(Test_os_exec, wait_return_code_false) 
{
    lib_exec_arg_t args {NULL};

    Libos_exec task("/usr/bin/false", args);
    
    ASSERT_EQ(0, task.init());    
    ASSERT_EQ(0, task.run());
    
    ASSERT_EQ(1, task.wait_child());
}

TEST_F(Test_os_exec, wait_return_code_true) 
{
    lib_exec_arg_t args {NULL};

    Libos_exec task("/usr/bin/true", args);
    
    ASSERT_EQ(0, task.init());    
    ASSERT_EQ(0, task.run());
    
    ASSERT_EQ(0, task.wait_child());
}

TEST_F(Test_os_exec, cat) 
{
    lib_exec_arg_t args {NULL};
    
    std::string input = "foo";
    
    lib_exec_buf_t output;
    lib_exec_buf_t expected = {'f', 'o', 'o'};

    Libos_exec task("/usr/bin/cat", args, input);
    
    ASSERT_EQ(0, task.init());    
    ASSERT_EQ(0, task.run());
    
    ASSERT_EQ(0, task.wait_child());
    
    ASSERT_EQ(0, task.get_std_out(output));
    
    ASSERT_EQ(expected, output);
}

TEST_F(Test_os_exec, largecat) 
{
    lib_exec_arg_t args {NULL};
    
    std::string input;
    lib_exec_buf_t expected;
    
    std::string pattern = "foo bar test";
    //16k+1 enough to exceed the page size (4k) in linux
    for(int i = 0; i < 0x4001; i++ ) {
        char ch = pattern.at(i%pattern.length());
        input.push_back(ch);
        expected.push_back(ch);
    }
    
    lib_exec_buf_t output;

    Libos_exec task("/usr/bin/cat", args, input);
    
    ASSERT_EQ(0, task.init());    
    ASSERT_EQ(0, task.run());
    
    ASSERT_EQ(0, task.wait_child());
    
    ASSERT_EQ(0, task.get_std_out(output));
    
    ASSERT_EQ(expected, output);
}

