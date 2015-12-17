from celery import shared_task

@shared_task
def task1():
    print(42)

@shared_task
def task2(model):
    model.number += 1
    model.save()
