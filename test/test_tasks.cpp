#include <gtest/gtest.h>
#include <../app/Tasks/TaskQueue.hpp>
#include <../app/Tasks/Task.hpp>

class TaskQueueTest : public testing::Test{
protected:
    TaskQueue queue;

    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(TaskQueueTest, PushPopTest){
    Task task("some/path", ENCRYPT);
    Task expected("some/path", ENCRYPT);

    queue.push(task);
    
    Task popedTask = queue.pop();
    if(popedTask.getPath() == expected.getPath() && popedTask.getStatus() == expected.getStatus()){
        SUCCEED();
    }
    else{
        FAIL();
    }

}

TEST_F(TaskQueueTest, EmptyTest){
    EXPECT_TRUE(queue.empty());
}