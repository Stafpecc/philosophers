/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarini <tarini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 20:00:28 by tarini            #+#    #+#             */
/*   Updated: 2025/03/17 20:00:44 by tarini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define INT_MAX __INT_MAX__
# define LONG_MAX __LONG_MAX__

# include <stdlib.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_data
{
	pthread_mutex_t mutex;
}	t_data;

// Philosophe == thread
// fourchette == Mutex

// thread == Prog asynchrone

// routine == manger - dormir - penser

// il y a autant de fourchette que de philo
// un philo ne peut manger qu'avec deux fourchette
// on doit afficher la mort dans maximum 10 millisecondes et stop le programme

// ecrire chaque changement de statut de philosophe

//./philo arg1 arg2 arg3 arg4 arg5

// arg1 = number_of_philosophers (nombre de philosophes et nombre de fourchettes)
// arg2 = time_to_die (s’il a pas mangé depuis time_to_die millisecondes il meurt)
// arg3 = time_to_eat (temps pour manger avec deux fourchettes en millisecondes)
// arg4 = time_to_sleep (temps pour dormir en milliseconde)
// arg5 = number_of_times_each_philosopher_must_eat (nombre de fois que chaque philosophe doit manger, arg optionnel)


#endif