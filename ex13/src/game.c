#include "../include/filler.h"
#include "../include/my_string.h"

void 			start_game(filler_t *filler)
{
	req_t   	*req;
	pos_t    	p;
	int 	  	ret;
	fd_set 		read_fds, write_fds;
	FILE 	  	*logg;
	struct timeval timeout;

	logg = fopen("filler.log", "w");
	fprintf(logg, "Start game\n");
	fclose(logg);

	create_req(req);
	set_nonblocking(0);

	while (true){
		FD_ZERO(&read_fds);
		FD_ZERO(&write_fds);

    if (filler->status == 1)
      FD_SET(1, &write_fds);
    else
      FD_SET(0, &read_fds);

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

		ret = select(2, &read_fds, &write_fds, NULL, &timeout);

		if (FD_ISSET(0, &read_fds)) {
			req = read_request(filler);

			logg = fopen("filler.log", "a");
			fprintf(logg, "\nRead complete\n");
			fclose(logg);

			if (req) {
				logg = fopen("filler.log", "a");
				fprintf(logg, "Request exists.\n");
				fclose(logg);

				p = play(req, filler);

        logg = fopen("filler.log", "a");
				fprintf(logg, "Playing position completed.\n");
				fclose(logg);

				filler->status = 1;
			}
		}

		if (FD_ISSET(1, &write_fds)){
			print_pos(p);

			logg = fopen("filler.log", "a");
			fprintf(logg, "Return position: \n");
			fclose(logg);

			filler->status = 0;
			string_destroy(filler->current_stream);
			filler->current_stream = NULL;
		}
	}
}

