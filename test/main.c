#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_data{
int cnt;
pthread_mutex_t mutex;
} t_data;

void *routine(void *p)
{
    int i = 0;
    t_data *data = (t_data *) p;
    pthread_mutex_lock(&data->mutex);
    while (i < 10000)
    {
        if(data->cnt == 15000)
        {
            pthread_mutex_unlock(&data->mutex);
            break;
        }
        data->cnt++;
        i++;
    }
    pthread_mutex_unlock(&data->mutex);
    return(NULL);
}

int main(void)
{
    pthread_t p1, p2;

    t_data *data;

    data = malloc(sizeof(t_data));
    data->cnt = 0;
    pthread_mutex_init(&data->mutex, NULL);

    pthread_create(&p1, NULL, &routine, data);
    pthread_create(&p2, NULL, &routine, data);

    pthread_join(p1, NULL);
	pthread_join(p2, NULL);

    pthread_mutex_destroy(&data->mutex);

	printf("cnt -> %d\n", data->cnt);
    free(data);

}
