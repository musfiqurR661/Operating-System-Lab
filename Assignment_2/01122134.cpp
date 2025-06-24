#include <cstdio>
#include <pthread.h>
#include <semaphore.h>
#include <queue>
#include <unistd.h>
using namespace std;


sem_t empty_sem;    // count of empty slots
sem_t full_sem;       // count of full buffer slots
pthread_mutex_t plate_lock;

queue<int> hot_plate; 
int next_dish_id = 1; // Global variable to track dish IDs


const int DISHES_PER_CHEF = 5;

const int HOT_PLATE_CAPACITY = 3;


int dishes_for_waiter[3] = {4, 3, 3};

// Initialize semaphores and mutex
void init_sync() {
    sem_init(&empty_sem, 0, HOT_PLATE_CAPACITY);
    sem_init(&full_sem,  0, 0);
    pthread_mutex_init(&plate_lock, nullptr);
}

void* chef_thread(void* arg) {
    int chef_id = *(int*)arg;

    //check if chef started cooking or not ;debugging purpose

    /*char msg[32];
    snprintf(msg, sizeof(msg), "Chef-%d starting", chef_id);
    printf("%s\n", msg);
    */


    for (int i = 0; i < DISHES_PER_CHEF; ++i) {
        
        sem_wait(&empty_sem);//down(empty)

        pthread_mutex_lock(&plate_lock);//down(mutex)

        
        sleep(1);
        int dish_id = next_dish_id++;
        hot_plate.push(dish_id);
        printf("Chef-%d prepared Dish-%d [Hot Plate: %ld/%d]\n",
               chef_id, dish_id, hot_plate.size(), HOT_PLATE_CAPACITY);

        
        pthread_mutex_unlock(&plate_lock); //up(mutex)


        sem_post(&full_sem); //up(full)
    }
    // printf("Chef-%d finished cooking\n", chef_id); // for me -> debug whether chef finished cooking or not
    return nullptr;
}

void* waiter_thread(void* arg) {
    int waiter_id = *(int*)arg;
    int to_serve = dishes_for_waiter[waiter_id - 1];
    // printf("Waiter-%d will serve %d dishes\n", waiter_id, to_serve); //for me to check how many dishes each waiter serves

    for (int i = 0; i < to_serve; ++i) {
        
        sem_wait(&full_sem);

        
        pthread_mutex_lock(&plate_lock);

        
        sleep(1);
        int dish_id = hot_plate.front();
        hot_plate.pop();
         printf("Waiter-%d served Dish-%d\n",
               waiter_id, dish_id, hot_plate.size());

        
        pthread_mutex_unlock(&plate_lock);

        
        sem_post(&empty_sem);
    }
    // printf("Waiter-%d finished serving\n", waiter_id); //for me -> debug whether waiter finished serving or not
    return nullptr;
}

int main() {
    init_sync();

    pthread_t chefs[2], waiters[3];
    int chef_ids[2]   = {1, 2};
    int waiter_ids[3] = {1, 2, 3};

    
    for (int i = 0; i < 2; ++i) {
        pthread_create(&chefs[i], nullptr, chef_thread, &chef_ids[i]);
    }
    
    for (int i = 0; i < 3; ++i) {
        pthread_create(&waiters[i], nullptr, waiter_thread, &waiter_ids[i]);
    }

    
    for (int i = 0; i < 2; ++i) {
        pthread_join(chefs[i], nullptr);
    }
    // printf("All chefs finished cooking\n");

    
    for (int i = 0; i < 3; ++i) {
        pthread_join(waiters[i], nullptr);
    }

    printf("All chefs finished cooking\n");
    printf("All waiters finished serving\n");

    return 0;
}
