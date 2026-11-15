#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#define PREFIX_LEN  4096
void get_broadcast_address(char *ip_addr, char mask, char *output_buffer) {
	//1. Convert the string ip address to uint8_t ip address (ip1, ip2, ip3, ip4)
	unsigned int ip1, ip2, ip3, ip4;
	sscanf(ip_addr,"%u.%u.%u.%u", &ip1, &ip2, &ip3, &ip4);

	//2. Convert all ips to a single 32 bit uint ip
	uint32_t ip_address = ((uint32_t)ip1 << 24) | ((uint32_t)ip2 << 16) | ((uint32_t)ip3 << 8) | (uint32_t)ip4;

	//3. Calulate subnet
	uint32_t subnet_mask = 0xFFFFFFFF;
	subnet_mask = subnet_mask << (32-mask);
	//Calculation for broadcast address
	ip_address = ip_address | (~ subnet_mask);

	//4. Convert 32 bit single ip into single ips
	ip1 = (ip_address >> 24) & 0xFF;
	ip2 = (ip_address >> 16) & 0xFF;
	ip3 = (ip_address >> 8) & 0xFF;
	ip4 = ip_address & 0xFF;

	//5. Convert ips to string
	sprintf(output_buffer, "%u.%u.%u.%u", ip1, ip2, ip3, ip4);

}
unsigned int get_ip_integer_equivalent(char *ip_addr) {
	unsigned int ip1, ip2, ip3, ip4;
	sscanf(ip_addr, "%u.%u.%u.%u", &ip1, &ip2, &ip3, &ip4);
	unsigned int ip_address = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
	return ip_address;
}
void get_abcd_ip_format(unsigned int ip_address) {
	unsigned int ip1, ip2, ip3, ip4;
	ip1 = (ip_address >> 24) & 0xFF;
	ip2 = (ip_address >> 16) & 0xFF;
	ip3 = (ip_address >> 8) & 0xFF;
	ip4 = ip_address & 0xFF;
	char output_buffer[PREFIX_LEN];
	memset(output_buffer,0,PREFIX_LEN);
	sprintf(output_buffer,"%u.%u.%u.%u", ip1, ip2, ip3, ip4);
	printf("ABCD format: %s\n", output_buffer);
}
void get_network_id(char *ip_addr, char mask, char *output_buffer) {
	//1. Convert the string ip address to uint8_t ip address (ip1, ip2, ip3, ip4)
	unsigned int ip1, ip2, ip3, ip4;
	sscanf(ip_addr,"%u.%u.%u.%u", &ip1, &ip2, &ip3, &ip4);

	//2. Convert all ips to a single 32 bit uint ip
	uint32_t ip_address = ((uint32_t)ip1 << 24) | ((uint32_t)ip2 << 16) | ((uint32_t)ip3 << 8) | (uint32_t)ip4;

	//3. Calulate subnet
	uint32_t subnet_mask = 0xFFFFFFFF;
	subnet_mask = subnet_mask << (32-mask);
	//Calculation for network id
	ip_address = ip_address & subnet_mask;

	//4. Convert 32 bit single ip into single ips
	ip1 = (ip_address >> 24) & 0xFF;
	ip2 = (ip_address >> 16) & 0xFF;
	ip3 = (ip_address >> 8) & 0xFF;
	ip4 = ip_address & 0xFF;

	//5. Convert ips to string
	sprintf(output_buffer, "%u.%u.%u.%u", ip1, ip2, ip3, ip4);
}
void get_subnet_cardinality(char mask){
    unsigned int max_N = 1U << (32 - mask);
    printf("Subnet cardinality for mask = %u is %u\n",mask, max_N);
}
int check_ip_subnet_membership(char *network_id, char mask, char *check_ip){
    unsigned int ip1, ip2, ip3, ip4;
    sscanf(check_ip,"%u.%u.%u.%u",&ip1, &ip2, &ip3, &ip4);
    unsigned int ip_address = (ip1 << 24) | (ip2 << 16) | (ip3 << 8) | ip4;
    unsigned int subnet_mask = 0xFFFFFFFFU << (32 - mask);
    ip_address = ip_address & subnet_mask;
    ip1 = (ip_address >> 24) & 0xFF;
    ip2 = (ip_address >> 16) & 0xFF;
    ip3 = (ip_address >> 8) & 0xFF;
    ip4 = ip_address & 0xFF;
    char ipadd_buffer[PREFIX_LEN];
	memset(ipadd_buffer,0,PREFIX_LEN);
	sprintf(ipadd_buffer,"%u.%u.%u.%u",ip1,ip2,ip3,ip4);
	if(strcmp(ipadd_buffer,network_id)==0){
	    return 0;
	}else{
	    return -1;
	}
}
int main()
{
	char ipadd_buffer[PREFIX_LEN];
	memset(ipadd_buffer,0,PREFIX_LEN);
	char *ip_add = "192.168.2.10";
	char mask = 20;
	get_broadcast_address(ip_add, mask, ipadd_buffer);
	printf("Broadcast address: %s\n", ipadd_buffer);
	unsigned int ip_address = get_ip_integer_equivalent(ip_add);
	printf("Ip address in integer format: %u\n",ip_address);
	get_abcd_ip_format(ip_address);
	memset(ipadd_buffer,0,PREFIX_LEN);
	get_network_id(ip_add, mask, ipadd_buffer);
	printf("Network Id: %s\n", ipadd_buffer);
	get_subnet_cardinality(mask);
	char *check_ip_add = "192.168.0.10";
	int result = check_ip_subnet_membership(ipadd_buffer,mask,check_ip_add);
	if(result==0){
	    printf("Ip address = %s is a member of subnet %s with mask %u\n", check_ip_add, ipadd_buffer, mask);
	}else{
	    printf("Ip address = %s is not a member of subnet %s with mask %u\n", check_ip_add, ipadd_buffer, mask);
	}
	return 0;
}
