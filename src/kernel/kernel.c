extern void main(){
	*(char*)0xb8000 = 'Q';
	*(char*)0xb8001 = 0x02;
	return;
}