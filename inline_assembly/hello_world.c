void print_string(char *buffer, int len)
{
	asm volatile (
		"mov $4, %%eax\n"
		"mov $1, %%ebx\n"
		"mov %0, %%ecx\n"
		"mov %1, %%edx\n"
		"int $0x80\n"
		:
		: "r"(buffer), "r"(len)
		: "eax", "ebx", "ecx", "edx");
}


int main()
{
	char *hello = "Hello World!\n";
	print_string(hello, 14);
	return 0;
}
