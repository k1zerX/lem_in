#include "ctnr.h"

void	ctnr_clear(t_ctnr *ctnr, void (*del)(t_elem *elem))
{
	while (ctnr->top)
		(*del)(ctnr_pop_top(ctnr));
}
