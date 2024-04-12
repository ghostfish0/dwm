void
fibonacci(Monitor *mon) {
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;
	
	nx = mon->wx;
	ny = 0;
	nw = mon->ww;
	nh = mon->wh;
	
  if (n == 1 || !mon->drawwithgaps) {
    mon->gappx = 0;
  }
  else 
    mon->gappx = gappx;

	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if((i % 2 && nh / 2 > 2 * c->bw)
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {
			if(i < n - 1) {
				if(i % 2)
					nh /= 2;
				else
					nw /= 2;
				if((i % 4) == 2)
					nx += nw;
				else if((i % 4) == 3)
					ny += nh;
			}
			if((i % 4) == 0)
        ny -= nh;
			else if((i % 4) == 1)
				nx += nw ;
			else if((i % 4) == 2) 
				ny += nh;
			else if((i % 4) == 3)
					nx -= nw;
			if(i == 0)
			{
				if(n != 1) {
          nw = mon->ww * mon->mfact;
          nh -= 2 * mon->gappx;
        }
				ny = mon->wy;
			}
			else if(i == 1)
				nw = mon->ww - nw - mon->gappx;
			i++;
		}
    if (n == 1) 
      resize(c, nx, ny, nw, nh, False);
    else
      resize(c, nx + mon->gappx, ny + mon->gappx, nw - 2 * c->bw - mon->gappx, nh - 2 * c->bw - mon->gappx, False);

	}
}

void
spiral(Monitor *mon) {
	fibonacci(mon);
}
