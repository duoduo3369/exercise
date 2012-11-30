package experiment._4;

import java.util.Arrays;

public class Problem_1 {
	int search(int[] array,int key){
		int low = 0;
		int high = array.length - 1;
		int mid;
		while(low <= high){
			mid = (low + high) / 2;
			if(array[mid] == key){
				return mid;
			}
			else if(array[mid] < key){
				low = mid + 1;
			}
			else{
				high = mid - 1;
			}
		}
		return -1;
	} 
	int searchRecursion(int[] array,int key,int low,int high){
		int mid;
		if(low < 0 || high >= array.length){
			return -1;
		}
		while(low <= high){
			mid = (low + high) / 2;
			if(array[mid] == key){
				return mid;
			}
			else if(array[mid] < key){
				return searchRecursion(array,key,mid+1,high);
			}
			else{
				return searchRecursion(array,key,low,mid - 1);
			}
		}
		return -1;
	}
	
	public static void main(String[] args) {
		int[] array = new int[]{1,3,2,4,5,6,0,9,7,8};
		Arrays.sort(array);
		for(int i :array){
			System.out.print(i+" ");
		}
		System.out.println();
		Problem_1 p = new Problem_1();
		int pos = p.search(array, 2);
		System.out.println(pos);
		pos = p.searchRecursion(array,19,0,array.length-1);
		System.out.println(pos);
	}

}
