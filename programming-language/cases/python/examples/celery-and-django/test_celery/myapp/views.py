from django.shortcuts import render

# Create your views here.
from django.views.generic.edit import CreateView
from django.views.generic.detail import DetailView
from django.core.urlresolvers import reverse
from django.http import JsonResponse
from .models import Test
from .tasks import task1, task2

class TestCreate(CreateView):
    model = Test
    fields = []

    def form_valid(self, form):
        success_url = super(TestCreate, self).form_valid(form)
        return JsonResponse({'result_url': success_url.url})

    def get_success_url(self):
        return reverse('myapp:test_detail', kwargs={'pk': self.object.id})

class TestDetail(DetailView):
    model = Test

    def get(self, request, *args, **kwargs):
        self.object = self.get_object()
        task1.delay()
        task2.delay(self.object)
        return JsonResponse({'number': self.object.number})
