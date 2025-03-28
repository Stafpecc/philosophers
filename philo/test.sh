#!/bin/bash

#1
if [[ "$(./philo 4 410 -200 200 20 | grep '1 has' | wc -l)" -eq 0 ]]; then
    echo "✅ parsing réussi"
else
    echo "❌ parsing échoué"
fi

#2
if [[ "$(./philo 4000 1010 333 333 20 | grep '1 has' | wc -l)" -eq 0 ]]; then
    echo "✅ parsing réussi"
else
    echo "❌ parsing échoué"
fi

#3
if [[ "$(./philo 200 810 200a 200 20 | grep '199 has' | wc -l)" -eq 0 ]]; then
    echo "✅ parsing réussi"
else
    echo "❌ parsing échoué"
fi

#1
if [[ "$(./philo 4 410 200 200 20 | grep '1 has' | wc -l)" -eq 40 && "$(./philo 4 410 200 200 20 | grep '0 has' | wc -l)" -eq 40 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#2
if [[ "$(./philo 3 1010 333 333 20 | grep '1 has' | wc -l)" -eq 40  && "$(./philo 3 1010 333 333 20 | grep '0 has' | wc -l)" -eq 40 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#3
if [[ "$(./philo 200 810 200 200 20 | grep '199 has' | wc -l)" -eq 40 && "$(./philo 200 810 200 200 20 | grep '198 has' | wc -l)" -eq 40 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#4
if [[ "$(./philo 3 1200 400 200 20 | grep '1 has' | wc -l)" -eq 40 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#5
if [[ "$(./philo 3 1200 200 400 20 | grep '1 has' | wc -l)" -eq 40 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#6
if [[ "$(./philo 200 810 400 200 20 | grep '199 has' | wc -l)" -eq 40 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#7
if [[ "$(./philo 3 1010 337 333 20 | grep '0 has' | wc -l)" -eq 2 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#8
if [[ "$(./philo 4 1000 400000 200 20 | grep '0 has' | wc -l)" -eq 2 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#9
if [[ "$(./philo 200 810 400 400000 20 | grep '199 has' | wc -l)" -eq 2 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi

#10
if [[ "$(./philo 1 810 200 200 20 | grep '0 has' | wc -l)" -eq 1 ]]; then
    echo "✅ Test réussi"
else
    echo "❌ Test échoué"
fi