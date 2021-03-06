for (I = problems ; I->f != 0; I++) 
{
  size_t i;
  double sum = 0, mean, sumd2 = 0, sd, res, err; 
  
  gsl_rng * r;

  if (I->dim > 3)
    {
      continue ;
    }

  r = gsl_rng_alloc (gsl_rng_default);

  for (i = 0; i < TRIALS ; i++)
    {
      MONTE_STATE *s = MONTE_ALLOC (I->dim);
      
      I->f->dim = I->dim;
      
      MONTE_INTEGRATE (I->f, I->xl, I->xu, 
                       I->dim, I->calls / MONTE_SPEEDUP, r, s,
                       &res, &err);
      
      gsl_test_abs (res, I->expected_result, 
                    5 * GSL_MAX(err, 1024*GSL_DBL_EPSILON), 
                    NAME ", %s, result[%d]", I->description, i);

      MONTE_ERROR_TEST (err, I->expected_error);

      result[i] = res;
      error[i] = err;
      
      MONTE_FREE (s);
    }

 for (i = 0; i < TRIALS; i++)
   {
     sum += result[i];
   }

 mean = sum / TRIALS ;

 for (i = 0; i < TRIALS; i++) 
   {
     sumd2 += pow(result[i] - mean, 2.0);
   }

 sd = sqrt(sumd2 / (TRIALS-1.0)) ;
 
 if (sd < TRIALS * GSL_DBL_EPSILON * fabs (mean))
   {
     sd = 0;
   }

 for (i = 0; i < TRIALS; i++)
   {
     if (sd == 0 && fabs(error[i]) < GSL_DBL_EPSILON * fabs(result[i]))
       {
         error[i] = 0.0;
       }

     gsl_test_factor (error[i], sd, 5.0,
                      NAME ", %s, abserr[%d] vs sd", I->description, i);
   }


  gsl_rng_free (r);
}

